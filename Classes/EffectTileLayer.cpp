#include "EffectTileLayer.h"
	
EffectTileLayer::EffectTileLayer()
{
}


EffectTileLayer::~EffectTileLayer()
{
	CC_SAFE_RELEASE(_effect);
}

EffectTileLayer * EffectTileLayer::create(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
{
	EffectTileLayer *ret = new (std::nothrow) EffectTileLayer();
	if (ret->initWithTilesetInfo(tilesetInfo, layerInfo, mapInfo))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

void EffectTileLayer::setEffect(LightEffect *effect)
{
	if (_effect != effect) 
	{
		CC_SAFE_RELEASE(_effect);
		_effect = effect;
		CC_SAFE_RETAIN(_effect);

		setGLProgramState(_effect->getGLProgramState());
	}
}

bool EffectTileLayer::initWithTilesetInfo(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
{

	if (tilesetInfo)
	{
		_texture = Director::getInstance()->getTextureCache()->addImage(tilesetInfo->_sourceImage);
		_texture->retain();

		std::size_t found = tilesetInfo->_sourceImage.find_last_of(".");
		std::string normal_map_path = tilesetInfo->_sourceImage;
		normal_map_path.insert(found, "_n");

		_normalmap = Director::getInstance()->getTextureCache()->addImage(normal_map_path);
	}

	// layerInfo
	_layerName = layerInfo->_name;
	_layerSize = layerInfo->_layerSize;
	_tiles = layerInfo->_tiles;
	_quadsDirty = true;
	setOpacity(layerInfo->_opacity);
	setProperties(layerInfo->getProperties());

	// tilesetInfo
	_tileSet = tilesetInfo;
	CC_SAFE_RETAIN(_tileSet);

	// mapInfo
	_mapTileSize = mapInfo->getTileSize();
	_layerOrientation = mapInfo->getOrientation();

	// offset (after layer orientation is set);
	Vec2 offset = this->calculateLayerOffset(layerInfo->_offset);
	this->setPosition(CC_POINT_PIXELS_TO_POINTS(offset));

	this->setContentSize(CC_SIZE_PIXELS_TO_POINTS(Size(_layerSize.width * _mapTileSize.width, _layerSize.height * _mapTileSize.height)));

	this->tileToNodeTransform();

	// shader, and other stuff
	setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

	_useAutomaticVertexZ = false;
	_vertexZvalue = 0;

	return true;
}

void EffectTileLayer::setLayerNormalmap()
{
	Node* tempNode;
	/*if (tempNode != nullptr)
		tempNode->removeFromParent();*/
	tempNode = Node::create();
	
	addChild(tempNode);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto offset = Node::convertToWorldSpace(this->getPosition());

	int minX = clampf((-offset.x) / getTileSet()->_tileSize.width, 0, getLayerSize().width - 1);
	int maxX = clampf((visibleSize.width - offset.x) / getTileSet()->_tileSize.width + 1, 0, getLayerSize().width - 1);

	int minY = clampf(getLayerSize().height - (visibleSize.height - offset.y) / getTileSet()->_tileSize.height, 0, getLayerSize().height - 1);
	int maxY = clampf(getLayerSize().height - (-offset.y) / getTileSet()->_tileSize.height + 1, 0, getLayerSize().height - 1);

	Size mapPixelSize;
	mapPixelSize.setSize(getLayerSize().width  * getTileSet()->_tileSize.width, getLayerSize().height * getTileSet()->_tileSize.height);

	for (int x = minX; x <= maxX; ++x)
	{
		for (int y = minY; y <= maxY; ++y)
		{
			int gid = getTileGIDAt(Vec2(x, y));
			if (gid)
			{
				Rect rect = _tileSet->getRectForGID(gid);
				rect = CC_RECT_PIXELS_TO_POINTS(rect);
				auto s = Sprite::createWithTexture(_normalmap, rect);
				s->setFlipY(true);
				Vec2 tempVec = getPositionAt(Vec2(x, y));
				tempVec.y += (((mapPixelSize.height - getTileSet()->_tileSize.height) / 2 - tempVec.y) * 2);
				s->setPosition(tempVec);
				s->setAnchorPoint(Vec2(0, 0));
				tempNode->addChild(s);
			}
		}
	}

	int i = (maxX - minX) * getTileSet()->_tileSize.width;
	int j = (maxY - minY) * getTileSet()->_tileSize.height;

	RenderTexture* invertedRT = RenderTexture::create((maxX - minX) * getTileSet()->_tileSize.width, (maxY - minY + 1) * getTileSet()->_tileSize.height);
	invertedRT->beginWithClear(1, 1, 1, 0);

	Vec2 tempVec = getPositionAt(Vec2(minX, minY));
	tempVec.y += (((mapPixelSize.height - getTileSet()->_tileSize.height) / 2 - tempVec.y) * 2);

	for (auto& child : tempNode->getChildren())
	{
		auto s = dynamic_cast<Sprite*>(child);
		if (s)
		{
			s->setPosition(s->getPosition() - tempVec);
			//s->draw(Director::getInstance()->getRenderer(), Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW), false);
			s->visit();
		}
	}

	invertedRT->end();

	//invertedRT->saveToFile("akbar.jpg");

	tempNode->removeFromParent();

	if (Sp != nullptr)
		Sp->removeFromParent();

	Sp = Sprite::createWithTexture(invertedRT->getSprite()->getTexture());
	Sp->setPosition(getPositionAt(Vec2(clampf(minX, 0, getLayerSize().width - 1), clampf(maxY, 0, getLayerSize().height - 1))) + Vec2(visibleSize.width / 2, visibleSize.height / 2));
	Sp->setOpacity(200);
	Sp->setAnchorPoint(Vec2(0.5, 0.5));

	addChild(Sp);
	//Sp->setVisible(false);
	_LayerNormalmap = Sp->getTexture();

	//tempNode->removeFromParent();
	

	/*RenderTexture* RT = RenderTexture::create(mapPixelSize.width, mapPixelSize.height);
	RT->beginWithClear(1, 1, 1, 0);
	invertedSp->visit();
	RT->end();

	invertedSp->removeFromParent();

	Sprite* Sp = Sprite::createWithTexture(RT->getSprite()->getTexture());
	Sp->setPosition(0, 0);
	Sp->setOpacity(200);
	Sp->setAnchorPoint(Vec2(0, 0));
	addChild(Sp);*/
}

void EffectTileLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	/*auto visibleSize = Director::getInstance()->getVisibleSize();
	auto offset = Node::convertToWorldSpace(this->getPosition());

	int minX = clampf((-offset.x) / getTileSet()->_tileSize.width, 0, getLayerSize().width);
	int maxX = clampf((visibleSize.width - offset.x) / getTileSet()->_tileSize.width + 1, 0, getLayerSize().width);

	int minY = clampf(getLayerSize().height - (visibleSize.height - offset.y) / getTileSet()->_tileSize.height, 0, getLayerSize().height);
	int maxY = clampf(getLayerSize().height - (-offset.y) / getTileSet()->_tileSize.height + 1, 0, getLayerSize().height);*/
	

	if (/*_LayerNormalmap == nullptr ||*/ flags != 0 || _dirty || _quadsDirty)
	{
		setLayerNormalmap();
	}
	if (_effect != nullptr)
	{
		_effect->prepareForRender(Sp, _LayerNormalmap);
	}
	experimental::TMXLayer::draw(renderer, transform, flags);
	renderer->render();
}
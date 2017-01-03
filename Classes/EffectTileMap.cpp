#include "EffectTileMap.h"


EffectTileMap::EffectTileMap()
{
}


EffectTileMap::~EffectTileMap()
{
}

EffectTileMap * EffectTileMap::create(const std::string& tmxFile)
{
	EffectTileMap *ret = new (std::nothrow) EffectTileMap();
	if (ret->initWithTMXFile(tmxFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool EffectTileMap::initWithTMXFile(const std::string& tmxFile)
{
	CCASSERT(tmxFile.size()>0, "FastTMXTiledMap: tmx file should not be empty");

	setContentSize(Size::ZERO);

	TMXMapInfo *mapInfo = TMXMapInfo::create(tmxFile);

	if (!mapInfo)
	{
		return false;
	}
	CCASSERT(!mapInfo->getTilesets().empty(), "FastTMXTiledMap: Map not found. Please check the filename.");
	buildWithMapInfo(mapInfo);

	return true;
}

void EffectTileMap::buildWithMapInfo(TMXMapInfo* mapInfo)
{
	_mapSize = mapInfo->getMapSize();
	_tileSize = mapInfo->getTileSize();
	_mapOrientation = mapInfo->getOrientation();

	_objectGroups = mapInfo->getObjectGroups();

	_properties = mapInfo->getProperties();

	_tileProperties = mapInfo->getTileProperties();

	int idx = 0;

	auto& layers = mapInfo->getLayers();
	for (const auto &layerInfo : layers) {
		if (layerInfo->_visible)
		{
			EffectTileLayer *child = parseLayer(layerInfo, mapInfo); // change
			if (child == nullptr) {
				idx++;
				continue;
			}
			addChild(child, idx, idx);

			// update content size with the max size
			const Size& childSize = child->getContentSize();
			Size currentSize = this->getContentSize();
			currentSize.width = std::max(currentSize.width, childSize.width);
			currentSize.height = std::max(currentSize.height, childSize.height);
			this->setContentSize(currentSize);

			idx++;
		}
	}
}

EffectTileLayer * EffectTileMap::parseLayer(TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
{
	TMXTilesetInfo *tileset = tilesetForLayer(layerInfo, mapInfo);
	if (tileset == nullptr)
		return nullptr;

	EffectTileLayer *layer = EffectTileLayer::create(tileset, layerInfo, mapInfo); // change

	// tell the layerinfo to release the ownership of the tiles map.
	layerInfo->_ownTiles = false;
	layer->setupTiles();

	return layer;
}
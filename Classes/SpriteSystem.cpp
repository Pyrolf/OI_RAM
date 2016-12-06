#include "SpriteSystem.h"

USING_NS_CC;

CSpriteSystem* CSpriteSystem::s_spriteSystemInstance = NULL;

CSpriteSystem::CSpriteSystem()
{

}

CSpriteSystem::~CSpriteSystem()
{
	for (int i = 0; i < textureInfoList.size(); i++)
	{
		textureInfoList[i].texture->release();
	}
	textureInfoList.clear();
}

// Instance Methods
CSpriteSystem* CSpriteSystem::getInstance()
{
	if (!s_spriteSystemInstance)
		s_spriteSystemInstance = new CSpriteSystem;
	return s_spriteSystemInstance;
}

void CSpriteSystem::destroy()
{
	if (s_spriteSystemInstance)
		delete s_spriteSystemInstance;
	s_spriteSystemInstance = NULL;
}

// Normal Methods
// Private Methods
Sprite* CSpriteSystem::createNewSpriteWithoutScale(const char *format, Size newSize)
{
	// Screen real dimensions
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Original image
	auto originalSprite = Sprite::create(format);
	auto oWidth = originalSprite->getContentSize().width;
	auto oHeight = originalSprite->getContentSize().height;
	originalSprite->setFlippedY(true);
	originalSprite->setScale(newSize.width / oWidth, newSize.height / oHeight);
	originalSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	
	// Create new texture with background in the exact size of the screen
	auto renderTexture = RenderTexture::create(newSize.width, newSize.height, Texture2D::PixelFormat::RGBA8888);
	renderTexture->setName(format);
	renderTexture->begin();
	originalSprite->visit();
	renderTexture->end();

	// Create new Sprite without scale, which perfoms much better
	auto newSprite = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());

	newSprite->getTexture()->retain();
	TextureInfo newTexturePath;
	sprintf(newTexturePath.originalPath, format);
	newTexturePath.texture = newSprite->getTexture();
	newTexturePath.size = newSize;
	newTexturePath.rect = newSprite->getTextureRect();
	textureInfoList.push_back(newTexturePath);

	return newSprite;
}
// Public Methods
Sprite* CSpriteSystem::getSprite(const char *format, Size newSize)
{
	Sprite* sprite = NULL;
	
	CSpriteSystem::TextureInfo* textureinfo = CSpriteSystem::getInstance()->getTextureInfo(format, newSize);
	
	if (textureinfo)
		sprite = Sprite::createWithTexture(textureinfo->texture);
	else
		sprite = CSpriteSystem::getInstance()->createNewSpriteWithoutScale(format, newSize);
	
	return sprite;
}
CSpriteSystem::TextureInfo* CSpriteSystem::getTextureInfo(const char *format, Size newSize)
{
	for (int i = 0; i < textureInfoList.size(); i++)
	{
		std::string originalPath = textureInfoList[i].originalPath;
		std::string formatPath = format;
		Size originalSize = textureInfoList[i].size;
		if (originalPath == formatPath &&
			originalSize.width == newSize.width &&
			originalSize.height == newSize.height)
		{
			return &textureInfoList[i];
		}
	}
	return NULL;
}
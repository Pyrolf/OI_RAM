#ifndef __SPRITE_SYSTEM_H__
#define __SPRITE_SYSTEM_H__

#include "cocos2d.h"

class CSpriteSystem
{
public:
	struct TextureInfo
	{
		char originalPath[100];
		cocos2d::Texture2D* texture;
		cocos2d::Rect rect;
	};

private:
	static CSpriteSystem* s_spriteSystemInstance;
	CSpriteSystem();
	~CSpriteSystem();

	std::vector<TextureInfo> textureInfoList;

	// Normal Methods
	cocos2d::Sprite* createNewSpriteWithoutScale(const char *format, cocos2d::Size newSize);
public:
	// Instance Methods
	static CSpriteSystem* getInstance();
	static void destroy();

	// Normal Methods
	cocos2d::Sprite* createSprite(const char *format, cocos2d::Size newSize);
	TextureInfo* getTextureInfo(const char *format);
};

#endif // __SPRITE_SYSTEM_H__

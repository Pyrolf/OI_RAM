#ifndef __SPRITE_LOADER_H__
#define __SPRITE_LOADER_H__

#include "cocos2d.h"

class CSpriteLoader
{
public:
	static void loadEnemiesSprites(cocos2d::Size size);
	static cocos2d::Sprite* getEnemySprite(cocos2d::Size size);

	static void loadPlayerSprites(cocos2d::Size size = cocos2d::Size(49, 90));
	static cocos2d::Sprite* getPlayerSprite(cocos2d::Size size = cocos2d::Size(49, 90));
};
#endif // __SPRITE_LOADER_H__

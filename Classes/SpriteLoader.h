#ifndef __SPRITE_LOADER_H__
#define __SPRITE_LOADER_H__

#include "cocos2d.h"

class CSpriteLoader
{
public:
	static void loadEnemiesSprites(cocos2d::Size size);
	static cocos2d::Sprite* getEnemySprite(cocos2d::Size size);
};
#endif // __SPRITE_LOADER_H__

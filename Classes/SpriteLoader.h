#ifndef __SPRITE_LOADER_H__
#define __SPRITE_LOADER_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "InteractableGameObject.h"

class CSpriteLoader
{
public:
	static void loadEnemySprites(CEnemy::ENEMY_TYPE type, cocos2d::Size size);
	static cocos2d::Sprite* getEnemySprite(CEnemy::ENEMY_TYPE type, cocos2d::Size size);

	static void loadProjectileSprites(cocos2d::Size size);
	static cocos2d::Sprite* getProjectileSprites(cocos2d::Size size);

	static void loadInteractiveItemSprites(CInteractableGameObject::TYPE type, cocos2d::Size size);
	static cocos2d::Sprite* getInteractiveItemSprites(CInteractableGameObject::TYPE type, cocos2d::Size size);

	static void loadPlayerSprites(cocos2d::Size size = cocos2d::Size(49, 90));
	static cocos2d::Sprite* getPlayerSprite(cocos2d::Size size = cocos2d::Size(49, 90));
};
#endif // __SPRITE_LOADER_H__

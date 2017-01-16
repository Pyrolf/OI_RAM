#ifndef __SPRITE_LOADER_H__
#define __SPRITE_LOADER_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "InteractableGameObject.h"
#include "PhysicsGameObject.h"

class CSpriteLoader
{
public:
	static void loadEnemySprites(CEnemy::ENEMY_TYPE type, cocos2d::Size size);
	static cocos2d::Sprite* getEnemySprite(CEnemy::ENEMY_TYPE type, cocos2d::Size size);

	static void loadProjectileSprites(cocos2d::Size size);
	static cocos2d::Sprite* getProjectileSprites(cocos2d::Size size);

	static void loadInteractiveItemSprites(CInteractableGameObject::TYPE type, cocos2d::Size size);
	static cocos2d::Sprite* getInteractiveItemSprites(CInteractableGameObject::TYPE type, cocos2d::Size size);

	static void loadPlayerSprites(cocos2d::Size size);
	static cocos2d::Sprite* getPlayerSprite(cocos2d::Size size);

	static void loadPhysicsGOSprites(CPhysicsGameObject::TYPE type, cocos2d::Size size);
	static cocos2d::Sprite* getPhysicsGOSprites(CPhysicsGameObject::TYPE type, cocos2d::Size size);
};
#endif // __SPRITE_LOADER_H__

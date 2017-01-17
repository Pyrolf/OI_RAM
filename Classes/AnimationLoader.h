#ifndef __ANIMATION_LOADER_H__
#define __ANIMATION_LOADER_H__

#include "cocos2d.h"
#include "Enemy.h"

class CAnimationLoader
{
public:
	static void loadEnemiesAnimates(CEnemy::ENEMY_TYPE type, cocos2d::Size size);
	static cocos2d::Animate* getEnemyAnimate(int state, CEnemy::ENEMY_TYPE type, cocos2d::Size size, float delay = 0.0f, unsigned int loops = 1);

	static void loadPlayerAnimates(cocos2d::Size size);
	static cocos2d::Animate* getPlayerAnimate(int state, cocos2d::Size size = cocos2d::Size(70, 90), float delay = 0.0f, unsigned int loops = 1);
};
#endif // __ANIMATION_LOADER_H__

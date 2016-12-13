#include "AnimationLoader.h"
#include "AnimationSystem.h"
#include "AIEnemy.h"
#include "Player.h"

USING_NS_CC;

void CAnimationLoader::loadEnemiesAnimates(cocos2d::Size size)
{
	CAnimationSystem::getInstance()->loadAnimation("animations/monsters/monster1/idle/frame_%d.png", size, 8);
	CAnimationSystem::getInstance()->loadAnimation("animations/monsters/monster1/walking/frame_%d.png", size, 8);
}

Animate* CAnimationLoader::getEnemyAnimate(int state, Size size, float delay, unsigned int loops)
{
	switch (state)
	{
		case CAIEnemy::FSM_IDLE:
		{
			return CAnimationSystem::getInstance()->getAnimate("animations/monsters/monster1/idle/frame_%d.png", size, 8, delay, loops);
			break;
		}
		case CAIEnemy::FSM_CHASE:
		{
			return CAnimationSystem::getInstance()->getAnimate("animations/monsters/monster1/walking/frame_%d.png", size, 8, delay, loops);
			break;
		}
	}
	return NULL;
}

void CAnimationLoader::loadPlayerAnimates(cocos2d::Size size)
{
	CAnimationSystem::getInstance()->loadAnimation("animations/knight/walking/frame_%d.png", size, 8);
}

Animate* CAnimationLoader::getPlayerAnimate(int state, Size size, float delay, unsigned int loops)
{
	switch (state)
	{
		case Player::A_Move:
		{
			return CAnimationSystem::getInstance()->getAnimate("animations/knight/walking/frame_%d.png", size, 8, delay, loops);
			break;
		}
	}
	return NULL;
}
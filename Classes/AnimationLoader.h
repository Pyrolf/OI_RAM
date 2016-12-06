#ifndef __ANIMATION_LOADER_H__
#define __ANIMATION_LOADER_H__

#include "cocos2d.h"

class CAnimationLoader
{
public:
	static void loadEnemiesAnimates(cocos2d::Size size);
	static cocos2d::Animate* getEnemyAnimate(int state, cocos2d::Size size, float delay = 0.0f, unsigned int loops = 1);
};
#endif // __ANIMATION_LOADER_H__
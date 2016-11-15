#ifndef __ANIMATION_SYSTEM_H__
#define __ANIMATION_SYSTEM_H__

#include "cocos2d.h"

class CAnimationSystem
{
private:
	static CAnimationSystem* s_animationSystemInstance;
	CAnimationSystem();
	~CAnimationSystem();

public:
	// Instance Methods
	static CAnimationSystem* getInstance();
	static void destroy();

	// Normal Methods
	cocos2d::Animate* getAnimate(const char *format, int count, float delay = 0.0f, unsigned int loops = 1);
	void loadAnimation(const char *format, int count);
};

#endif // __ANIMATION_SYSTEM_H__

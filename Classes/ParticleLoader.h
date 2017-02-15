#ifndef __PARTICLE_LOADER_H__
#define __PARTICLE_LOADER_H__

#include "cocos2d.h"

class CParticleLoader
{
public:
	static cocos2d::ParticleSystem* createBleedingEffect(	cocos2d::Node* target,
															int totalParticles = 15,
															float duration = 0.5f,
															float life = 1.5f,
															cocos2d::Vec2 offsetPosition = cocos2d::Vec2::ANCHOR_BOTTOM_LEFT,
															cocos2d::Color4F color = cocos2d::Color4F::RED,
															float sizeScale = 0.05f);

	static cocos2d::ParticleSystem* createSmokeEffect();
	static cocos2d::ParticleSystem* createSlowEffect();
	static cocos2d::ParticleSystem* createSlamEffect();
};
#endif // __PARTICLE_LOADER_H__

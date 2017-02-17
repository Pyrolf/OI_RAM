#include "ParticleLoader.h"

USING_NS_CC;

ParticleSystem* CParticleLoader::createBleedingEffect(	Node* target,
														int totalParticles,
														float duration,
														float life,
														Vec2 offsetPosition,
														Color4F color,
														float sizeScale)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Bleeding effect
	ParticleExplosion* m_bleeding = ParticleExplosion::create();

	// Set total amount of  particles
	m_bleeding->initWithTotalParticles(totalParticles);
	m_bleeding->setEmissionRate(totalParticles / duration);
	// Set duration
	m_bleeding->setDuration(duration);
	// Set life of particle
	m_bleeding->setLife(life);
	m_bleeding->setLifeVar(0.0f);

	// Set Position
	m_bleeding->setPosition(target->getPosition() + offsetPosition);

	// Set color: red
	m_bleeding->setStartColor(color);
	m_bleeding->setStartColorVar(color);
	m_bleeding->setEndColor(color);
	m_bleeding->setEndColorVar(color);

	// Set size
	m_bleeding->setStartSize(visibleSize.width * sizeScale);
	m_bleeding->setStartSizeVar(0.0f);
	m_bleeding->setEndSize(0.0f);
	m_bleeding->setEndSizeVar(0.0f);

	// Set Gravity
	m_bleeding->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	m_bleeding->setGravity(Vec2(0, -90));

	// Set target
	target->getParent()->addChild(m_bleeding);

	return m_bleeding;
}


ParticleSystem* CParticleLoader::createSmokeEffect()
{
	auto p = cocos2d::CCParticleSystemQuad::create("particle/smoke.plist");
	p->setPosition(Vec2::ZERO);

	return p;
}

ParticleSystem* CParticleLoader::createSlowEffect()
{
	auto p = cocos2d::CCParticleSystemQuad::create("particle/slow.plist");
	p->setPosition(Vec2::ZERO);

	return p; 
}

ParticleSystem* CParticleLoader::createSlamEffect()
{
	auto p = cocos2d::CCParticleSystemQuad::create("particle/slam.plist");
	p->setPosition(Vec2::ZERO);

	return p;
}

ParticleSystem* CParticleLoader::createHitmarkerEffect()
{
	auto p = cocos2d::CCParticleSystemQuad::create("particle/hitmarker.plist");
	auto t = Director::getInstance()->getTextureCache()->addImage("images/hitmarker.png");
	p->setTexture(t);
	p->setPosition(Vec2::ZERO);

	return p;
}
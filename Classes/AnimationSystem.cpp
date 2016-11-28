#include "AnimationSystem.h"
#include "SpriteSystem.h"

USING_NS_CC;

CAnimationSystem* CAnimationSystem::s_animationSystemInstance = NULL;

CAnimationSystem::CAnimationSystem()
{

}

CAnimationSystem::~CAnimationSystem()
{
}

// Instance Methods
CAnimationSystem* CAnimationSystem::getInstance()
{
	if (!s_animationSystemInstance)
		s_animationSystemInstance = new CAnimationSystem;
	return s_animationSystemInstance;
}

void CAnimationSystem::destroy()
{
	if (s_animationSystemInstance)
		delete s_animationSystemInstance;
	s_animationSystemInstance = NULL;
}

// Normal Methods
// Public Methods
Animate* CAnimationSystem::getAnimate(const char *format, Size newSize, int count, float delay/* = 0.0f*/, unsigned int loops/* = 1*/)
{
	auto animation = Animation::create();
	char str[100];
	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		CSpriteSystem::TextureInfo* textureInfo = CSpriteSystem::getInstance()->getTextureInfo(str, newSize);
		animation->addSpriteFrameWithTexture(textureInfo->texture, textureInfo->rect);
	}
	animation->setDelayPerUnit(delay);
	animation->setLoops(loops);
	return Animate::create(animation);
}


void CAnimationSystem::loadAnimation(const char *format, Size newSize, int count)
{
	char str[100];
	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		CSpriteSystem::getInstance()->createSprite(str, newSize);
	}
}
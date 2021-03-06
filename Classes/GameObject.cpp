#include "GameObject.h"
#include "SpriteSystem.h"

USING_NS_CC;

CGameObject::CGameObject()
	: m_pSprite(NULL)
	, m_spriteSize(Vec2::ANCHOR_BOTTOM_LEFT)
	, m_bActive(false)
	, m_nLives(1)
{
}

CGameObject::~CGameObject()
{
}

CGameObject* CGameObject::create()
{
	CGameObject * ret = new (std::nothrow) CGameObject();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void CGameObject::MinusLives(int nDamage)
{
	m_nLives -= nDamage;
}

// Setters
void CGameObject::SetSprite(cocos2d::Sprite* sprite, cocos2d::Size size)
{
	this->removeChild(m_pSprite);
	m_pSprite = sprite;
	m_spriteSize = size;
	this->addChild(m_pSprite);
}
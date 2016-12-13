#include "GameObject.h"
#include "SpriteSystem.h"

USING_NS_CC;

CGameObject::CGameObject()
	: m_pSprite(NULL)
	, m_spriteSize(Vec2::ANCHOR_BOTTOM_LEFT)
	, m_bActive(false)
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

// Setters
void CGameObject::SetSprite(cocos2d::Sprite* sprite, cocos2d::Size size)
{
	m_pSprite = sprite;
	m_spriteSize = size;
	this->addChild(m_pSprite);
}
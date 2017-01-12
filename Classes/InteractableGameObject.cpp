#include "InteractableGameObject.h"
#include "InGameScene.h"

USING_NS_CC;

CInteractableGameObject::CInteractableGameObject()
	: CGameObject()
	, m_eType(COIN)
	, m_pTargetGO(NULL)
{
}

CInteractableGameObject::~CInteractableGameObject()
{
}

CInteractableGameObject* CInteractableGameObject::create()
{
	CInteractableGameObject * ret = new (std::nothrow) CInteractableGameObject();
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

bool CInteractableGameObject::CheckCollision()
{
	auto rect = this->GetSprite()->getBoundingBox();
	rect.setRect(this->getPositionX(), this->getPositionY(), rect.size.width, rect.size.height);
	auto targetRect = m_pTargetGO->GetSprite()->getBoundingBox();
	targetRect.setRect(m_pTargetGO->getPositionX(), m_pTargetGO->getPositionY(), targetRect.size.width, targetRect.size.height);

	if (rect.intersectsRect(targetRect))
	{
		return true;
	}

	return false;
}

CCoin::CCoin()
	: CInteractableGameObject()
{
}

CCoin::~CCoin()
{
}
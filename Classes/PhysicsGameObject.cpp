#include "PhysicsGameObject.h"
#include "CollisionManager.h"
#include "GameObjectManager.h"

USING_NS_CC;

CPhysicsGameObject::CPhysicsGameObject()
	: CGameObject()
{
}

CPhysicsGameObject::~CPhysicsGameObject()
{
}

CPhysicsGameObject* CPhysicsGameObject::create()
{
	CPhysicsGameObject * ret = new (std::nothrow) CPhysicsGameObject();
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

void CPhysicsGameObject::GeneratePhysicsBody()
{
	PhysicsBody* Body;
	Body = PhysicsBody::createBox(GetSprite()->getContentSize());
	Body->setMass(1);

	switch (type)
	{
	case CRATE:
		Body->setCollisionBitmask(CCollisionManager::CB_CRATE);
		Body->setMass(1000);
		Body->setRotationEnable(false);
		break;

	case JUMPPAD:
		Body->setCollisionBitmask(CCollisionManager::CB_JUMPAD);
		Body->setDynamic(false);
		break;
	};
	
	Body->setContactTestBitmask(1);

	setPhysicsBody(Body);
}

void CPhysicsGameObject::DestroyCrate()
{
	if (type == CRATE)
	{
		this->getPhysicsBody()->setEnabled(false);
		auto flickAction = CallFunc::create([this]()
		{
			this->setVisible(!this->isVisible());
		});
		float fTimeInterval = 0.1f;
		auto sequence = Sequence::createWithTwoActions(flickAction, DelayTime::create(fTimeInterval));
		auto repeat = Repeat::create(sequence, 0.5f / fTimeInterval);
		auto checkAction = CallFunc::create([this]()
		{
			((CGameObjectManager*) this->getParent())->SpawnInteractableItem(this->getPosition(), (CInteractableGameObject::TYPE)cocos2d::RandomHelper::random_int(0, CInteractableGameObject::TYPE::NUM_OF_TYPES-2));

			this->SetActive(false);
			this->pause();
			this->setVisible(false);
		});
		auto sequence2 = Sequence::createWithTwoActions(repeat, checkAction);
		this->runAction(sequence2);
	}
}
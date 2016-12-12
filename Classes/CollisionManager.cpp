#include "CollisionManager.h"
#include "Player.h"
USING_NS_CC;

CCollisionManager::CCollisionManager()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CCollisionManager::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(CCollisionManager::onContactSeparate, this);
	//contactListener->onContactPreSolve = CC_CALLBACK_2(CCollisionManager::onContactPreSolve, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Update(float dt)
{
}

bool CCollisionManager::onContactBegin(PhysicsContact& contact)
{
	PhysicsShape* shape[2];
	shape[0] = contact.getShapeA();
	shape[1] = contact.getShapeB();

	if (shape[0]->getCollisionBitmask() == shape[1]->getCollisionBitmask())
	{
		return false;
	}
	else if (shape[0]->getCollisionBitmask() == CB_PLAYER || shape[1]->getCollisionBitmask() == CB_PLAYER)
	{
		int self = (shape[0]->getCollisionBitmask() == CB_PLAYER ? 0 : 1);
		int other = !self;

		if (shape[self]->isSensor())
		{
			if (shape[other]->getCollisionBitmask() == CB_GROUND)
			{
				if (fabs(contact.getContactData()->normal.y) > 0.9)
				{
					auto player = dynamic_cast<Player*>(shape[self]->getBody()->getNode());
					if (player)
					{
						player->SetJumpCount(0);
						player->SetFrictionMulti(GROUND_FRICTION_MULTI);
					}
				}
			}
		}
	}

	return true;
}

void CCollisionManager::onContactSeparate(PhysicsContact& contact)
{
	PhysicsShape* shape[2];
	shape[0] = contact.getShapeA();
	shape[1] = contact.getShapeB();

	
	if (shape[0]->getCollisionBitmask() == CB_PLAYER || shape[1]->getCollisionBitmask() == CB_PLAYER)
	{
		int self = (shape[0]->getCollisionBitmask() == CB_PLAYER ? 0 : 1);
		int other = !self;

		if (shape[self]->isSensor())
		{
			if (shape[other]->getCollisionBitmask() == CB_GROUND)
			{
				auto player = dynamic_cast<Player*>(shape[self]->getBody()->getNode());
				if (player)
				{
					player->SetFrictionMulti(AIR_FRICTION_MULTI);
				}
			}
		}
	}
}

//bool CCollisionManager::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve) 
//{
//	solve.setRestitution(0);
//
//	contact.getShapeA()->getBody()->resetForces();
//	contact.getShapeB()->getBody()->resetForces();
//
//	return true;
//}
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
	PhysicsBody* body[2];
	body[0] = contact.getShapeA()->getBody();
	body[1] = contact.getShapeB()->getBody();

	if (body[0]->getCollisionBitmask() == body[1]->getCollisionBitmask())
	{
		return false;
	}
	else if (body[0]->getCollisionBitmask() == CB_PLAYER_BOTTOM || body[1]->getCollisionBitmask() == CB_PLAYER_BOTTOM)
	{
		int self = (body[0]->getCollisionBitmask() == CB_PLAYER_BOTTOM ? 0 : 1);
		int other = !self;
		if (body[other]->getCollisionBitmask() == CB_GROUND)
		{
			if (contact.getContactData()->normal.y == -1)
			{
				auto player = dynamic_cast<Player*>(body[self]->getNode()->getParent());
				if (player)
				{
					player->SetJumpCount(0);
					player->SetFrictionMulti(GROUND_FRICTION_MULTI);
				}
			}
		}
		return false;
	}

	return true;
}

void CCollisionManager::onContactSeparate(PhysicsContact& contact)
{
	PhysicsBody* body[2];
	body[0] = contact.getShapeA()->getBody();
	body[1] = contact.getShapeB()->getBody();

	
	if (body[0]->getCollisionBitmask() == CB_PLAYER_BOTTOM || body[1]->getCollisionBitmask() == CB_PLAYER_BOTTOM)
	{
		int self = (body[0]->getCollisionBitmask() == CB_PLAYER_BOTTOM ? 0 : 1);
		int other = !self;
		if (body[other]->getCollisionBitmask() == CB_GROUND)
		{
			auto player = dynamic_cast<Player*>(body[self]->getNode()->getParent());
			if (player)
			{
				player->SetFrictionMulti(AIR_FRICTION_MULTI);
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
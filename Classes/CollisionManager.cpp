#include "CollisionManager.h"
#include "Player.h"
#include "Enemy.h"
#include "AIEnemy.h"

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

		auto player = dynamic_cast<Player*>(shape[self]->getBody()->getNode());
		
		if (shape[self]->isSensor())
		{
			if (shape[other]->getCollisionBitmask() == CB_GROUND)
			{
				if (fabs(contact.getContactData()->normal.y) > 0.9)
				{
					if (player)
					{
						player->SetJumpCount(0);
						player->SetFrictionMulti(GROUND_FRICTION_MULTI);
					}
				}
			}
			if (shape[other]->getCollisionBitmask() == CB_ENEMY)
			{
				if (player)
				{
					CEnemy* enemy = dynamic_cast<CEnemy*>(shape[other]->getBody()->getNode());

					enemy->MinusLives();
					if (enemy->GetLives() <= 0)
					{
						dynamic_cast<CEnemy*>(shape[other]->getBody()->getNode())->getPhysicsBody()->setContactTestBitmask(0);
						dynamic_cast<CEnemy*>(shape[other]->getBody()->getNode())->getPhysicsBody()->setRotationEnable(true);
						dynamic_cast<CEnemy*>(shape[other]->getBody()->getNode())->getPhysicsBody()->setAngularVelocity(30);
						dynamic_cast<CEnemy*>(shape[other]->getBody()->getNode())->getPhysicsBody()->applyImpulse(Vec2(random(-1.0f, 1.0f), random(0, 1)) * 1000);
					}
				}
			}
		}
		else
		{
			if (shape[other]->getCollisionBitmask() == CB_ENEMY)
			{
				if (player)
				{
					Vec2 epos = shape[other]->getBody()->getNode()->convertToWorldSpace(shape[other]->getBody()->getNode()->getPosition());
					Vec2 ppos = player->convertToWorldSpace(player->getPosition());
					
					player->Knockback((ppos - epos).getNormalized(), 800);
					player->SetFrictionMulti(0);
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

void CCollisionManager::addPhysicBody(CEnemy* target)
{
	if (target->getPhysicsBody())
		target->removeComponent(target->getPhysicsBody());

	auto body = PhysicsBody::createBox(target->GetSprite()->getContentSize(), PhysicsMaterial(1, 0.4f, 1));
	body->setRotationEnable(false);

	body->setCollisionBitmask(CCollisionManager::CB_ENEMY);
	body->setContactTestBitmask(1);

	target->setPhysicsBody(body);
}
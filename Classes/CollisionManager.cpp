#include "CollisionManager.h"
#include "Player.h"
#include "Enemy.h"
#include "AIEnemy.h"
#include "PhysicsGameObject.h"
#include "SoundLoader.h"

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

	/*if (shape[0]->getCollisionBitmask() == shape[1]->getCollisionBitmask())
	{
		return false;
	}
	else */if (shape[0]->getCollisionBitmask() == CB_PLAYER || shape[1]->getCollisionBitmask() == CB_PLAYER)
	{
		int self = (shape[0]->getCollisionBitmask() == CB_PLAYER ? 0 : 1);
		int other = !self;

		auto player = dynamic_cast<Player*>(shape[self]->getBody()->getNode());
		
		if (shape[self]->getTag() == 69)
		{
			if (shape[other]->getCollisionBitmask() == CB_GROUND)
			{
				if (fabs(contact.getContactData()->normal.y) > 0.9)
				{
					if (player)
					{
						player->SetJumpCount(0);
						//player->SetFrictionMulti(GROUND_FRICTION_MULTI);
					}

					return true;
				}
			}
			else if (shape[other]->getCollisionBitmask() == CB_ENEMY)
			{
				if (fabs(contact.getContactData()->normal.y) > 0.9)
				{
					CEnemy* enemy = dynamic_cast<CEnemy*>(shape[other]->getBody()->getNode());

					if (player->GetActiveSkill() == Player::ACTIVE_SKILL::Invisible)
					{
						player->ResetSkillEffect();
					}
					if (player->GetActiveSkill() == Player::ACTIVE_SKILL::Slam)
						enemy->MinusLives(2);
					else
						enemy->MinusLives(1);

					if (enemy->GetLives() <= 0)
					{
						dynamic_cast<CEnemy*>(shape[other]->getBody()->getNode())->getPhysicsBody()->setCollisionBitmask(0);
						//dynamic_cast<CEnemy*>(shape[other]->getBody()->getNode())->getPhysicsBody()->setRotationEnable(true);
						//dynamic_cast<CEnemy*>(shape[other]->getBody()->getNode())->getPhysicsBody()->setAngularVelocity(1);
						dynamic_cast<CEnemy*>(shape[other]->getBody()->getNode())->getPhysicsBody()->applyImpulse(Vec2(random(-1.0f, 1.0f), random(0, 1)) * 500);
					}

					player->getPhysicsBody()->setVelocity(Vec2::ZERO);
					player->getPhysicsBody()->applyImpulse(Vec2(0, 400));

					enemy->getPhysicsBody()->setVelocity(Vec2::ZERO);

					return true;
				}
			}
			else if (shape[other]->getCollisionBitmask() == CB_CRATE)
			{
				if (fabs(contact.getContactData()->normal.y) > 0.9)
				{
					if (player)
					{
						player->SetJumpCount(0);
						player->getPhysicsBody()->setVelocity(Vec2::ZERO);
						player->getPhysicsBody()->applyImpulse(Vec2(0, 400));
					}
					dynamic_cast<CPhysicsGameObject*>(shape[other]->getBody()->getNode())->DestroyCrate();

					CSoundLoader::playSoundEffect(CSoundLoader::SMASH_SOUND_EFFECT);

					return true;
				}
			}
			else if (shape[other]->getCollisionBitmask() == CB_JUMPAD)
			{
				if (fabs(contact.getContactData()->normal.y) > 0.9)
				{
					if (player)
					{
						player->SetJumpCount(0);
						player->getPhysicsBody()->setVelocity(Vec2::ZERO);
						player->getPhysicsBody()->applyImpulse(Vec2(0, 800));
					}

					CSoundLoader::playSoundEffect(CSoundLoader::BOUNCE_SOUND_EFFECT);

					return true;
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
					
					//damage and knockback player
					if (player->GetActiveSkill() == Player::ACTIVE_SKILL::Invisible)
					{
						player->ResetSkillEffect();
					}
					player->ReceiveDamage();
					player->getPhysicsBody()->setVelocity(Vec2::ZERO);
					player->getPhysicsBody()->applyImpulse((ppos - epos).getNormalized() * 200);
					//player->SetFrictionMulti(0);

					//knockback enemy
					CEnemy* enemy = dynamic_cast<CEnemy*>(shape[other]->getBody()->getNode());
					if (enemy->GetAI()->GetCurrentState() == CAIEnemy::FSM_POUNCE)
						enemy->GetAI()->PounceCoolDown();

					enemy->getPhysicsBody()->applyImpulse((epos - ppos).getNormalized() * 200);
			

					return true;
				}
			}
		}
	}
	if (shape[0]->getCollisionBitmask() == CB_ENEMY_BULLET || shape[1]->getCollisionBitmask() == CB_ENEMY_BULLET)
	{
		int self = (shape[0]->getCollisionBitmask() == CB_ENEMY_BULLET ? 0 : 1);
		int other = !self;

		if (shape[other]->getCollisionBitmask() == CB_PLAYER)
		{
			auto player = dynamic_cast<Player*>(shape[other]->getBody()->getNode());

			if (player->GetActiveSkill() == Player::ACTIVE_SKILL::Invisible)
			{
				player->ResetSkillEffect();
			}

			player->ReceiveDamage();
		}
		if (shape[other]->getCollisionBitmask() == CB_PLAYER || shape[other]->getCollisionBitmask() == CB_GROUND)
		{
			auto destroyProjectile = RemoveSelf::create();

			auto sequence = Sequence::create(destroyProjectile, NULL);
			shape[self]->getBody()->getNode()->stopAllActions();
			shape[self]->getBody()->getNode()->runAction(sequence);

			return true;
		}
		else
			return false;

	}

	return true;
}

void CCollisionManager::onContactSeparate(PhysicsContact& contact)
{
//	PhysicsShape* shape[2];
//	shape[0] = contact.getShapeA();
//	shape[1] = contact.getShapeB();
//
//	
//	if (shape[0]->getCollisionBitmask() == CB_PLAYER || shape[1]->getCollisionBitmask() == CB_PLAYER)
//	{
//		int self = (shape[0]->getCollisionBitmask() == CB_PLAYER ? 0 : 1);
//		int other = !self;
//
//		if (shape[self]->isSensor())
//		{
//			if (shape[other]->getCollisionBitmask() == CB_GROUND)
//			{
//				auto player = dynamic_cast<Player*>(shape[self]->getBody()->getNode());
//				if (player)
//				{
//					player->SetFrictionMulti(AIR_FRICTION_MULTI);
//				}
//			}
//		}
//	}
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

	body->setCollisionBitmask(CCollisionManager::CB_ENEMY);
	body->setContactTestBitmask(1);

	body->setMass(1);
	body->setRotationEnable(false);

	target->setPhysicsBody(body);
}

void CCollisionManager::addPhysicBodyEnemyBullet(cocos2d::Sprite* target)
{
	auto body = PhysicsBody::createBox(target->getContentSize());

	body->setCollisionBitmask(CCollisionManager::CB_ENEMY_BULLET);
	body->setContactTestBitmask(1);

	body->setGravityEnable(false);
	body->getShapes().at(0)->setSensor(true);

	target->setPhysicsBody(body);
}
#include "Player.h"
#include "CollisionManager.h"
#include "KeyboardManager.h"
#include "SpriteLoader.h"
#include "AnimationLoader.h"
#include "ParticleLoader.h"
#include "SoundLoader.h"

Player::Player()
: CGameObject()
{
}

Player::~Player()
{
}

void Player::Init(Vec2 Pos)
{
	this->setPosition(Pos);

	Sprite* temp = CSpriteLoader::getPlayerSprite(Size(50 , 86));
	auto spriteSize = temp->getContentSize();

	this->SetSprite(temp, spriteSize);
	astate = A_Idle;

	PhysicsBody* Body;
	Body = PhysicsBody::createBox(Size(spriteSize.width, spriteSize.height - 4), PhysicsMaterial(1, 0, 0), Vec2(0, 2));
	Body->addShape(PhysicsShapeBox::create(Size(spriteSize.width, 4), PhysicsMaterial(1, 0, 0.4), Vec2(0, -spriteSize.height / 2 + 2)));
	Body->getShapes().at(1)->setTag(69);
	Body->setMass(1);
	Body->setRotationEnable(false);

	Body->setCollisionBitmask(CCollisionManager::CB_PLAYER);
	Body->setContactTestBitmask(1);

	setPhysicsBody(Body);


	//Body = PhysicsBody::createBox(Size(spriteSize.width - 2, 4), PhysicsMaterial(1, 0, 0), Vec2(0, -spriteSize.height / 2 + 2));
	//Body->setMass(1);
	//Body->setDynamic(false);

	//Body->setCollisionBitmask(CCollisionManager::CB_PLAYER_BOTTOM);
	//Body->setContactTestBitmask(1);

	//auto n = Node::create();
	//n->setPhysicsBody(Body);
	//addChild(n);

	activeSkill = ACTIVE_SKILL::None;

	maxMana = 25;
	mana = maxMana;
	manaRegenRate = 1;

	moveLeft = moveRight = false;
}

void Player::Update(float dt)
{
	if (GetLives() > 0)
	{
		Movement(dt);

		UpdateSkills(dt);

		if (mana < maxMana && activeSkill == ACTIVE_SKILL::None)
		{
			mana += manaRegenRate * dt;
			if (mana > maxMana)
				mana = maxMana;
		}

		//auto Body = this->getPhysicsBody();

		//if (Body->getVelocity().length > 0 && frictionLerpValue > 0)

		if (!isMoving)
		{
			setA_Idle();
		}

		isMoving = false;
	}
}

bool downKeypress = false;
bool ZKeypress = false;
bool XKeypress = false;

void Player::UpdateSkills(float dt)
{
#if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC))
	if ((KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) && !downKeypress))
	{
		UseSkills(ACTIVE_SKILL::Slam);

		downKeypress = true;
	}
	else if (!KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) && downKeypress)
	{
		downKeypress = false;
	}

	if ((KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_Z) && !ZKeypress))
	{
		UseSkills(ACTIVE_SKILL::Invisible);
		
		ZKeypress = true;
	}
	else if (!KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_Z) && ZKeypress)
	{
		ZKeypress = false;
	}

	if ((KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_X) && !XKeypress))
	{
		UseSkills(ACTIVE_SKILL::Slow);

		XKeypress = true;
	}
	else if (!KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_X) && XKeypress)
	{
		XKeypress = false;
	}
#endif

	switch (activeSkill)
	{
		case ACTIVE_SKILL::Slam:
			slamSkillActiveTime -= dt;
			if (slamSkillActiveTime < 0)
				activeSkill = ACTIVE_SKILL::None;
		break;

		case ACTIVE_SKILL::Invisible:
			mana -= 5 * dt;
			if (mana < 0)
			{
				mana = 0;
				activeSkill = ACTIVE_SKILL::None;
				ResetSkillEffect();
			}
		break;

		case ACTIVE_SKILL::Slow:
			mana -= 14 * dt;
			if (mana < 0)
			{
				mana = 0;
				activeSkill = ACTIVE_SKILL::None;
				ResetSkillEffect();
			}
		break;
	}
}

void Player::UseSkills(ACTIVE_SKILL s)
{
	switch (s)
	{
	case ACTIVE_SKILL::Slam:
		{
			if (activeSkill != ACTIVE_SKILL::Slam && mana > 10)
			{
				ResetSkillEffect();

				activeSkill = ACTIVE_SKILL::Slam;
			
				this->getPhysicsBody()->setVelocity(Vec2::ZERO);
				this->getPhysicsBody()->applyImpulse(Vec2(0, -500));

				slamSkillActiveTime = 0.5f;
				mana -= 10;

				ParticleSystem *p = CParticleLoader::createSlamEffect();
				this->addChild(p);
				p->setPosition(Vec2(0, -this->GetSprite()->getContentSize().height * 0.5));

				CSoundLoader::playSoundEffect(CSoundLoader::SHUSH_SOUND_EFFECT);
			}
		}
		break;

	case ACTIVE_SKILL::Invisible:
		{
			if (activeSkill != ACTIVE_SKILL::Invisible && mana > 1)
			{
				ResetSkillEffect();
				activeSkill = ACTIVE_SKILL::Invisible;
				GetSprite()->setOpacity(160);

				this->addChild(CParticleLoader::createSmokeEffect());

				CSoundLoader::playSoundEffect(CSoundLoader::SUCK_SOUND_EFFECT);
			}
			else
			{
				ResetSkillEffect();
			}
		}
		break;

	case ACTIVE_SKILL::Slow:
		{
			if (activeSkill != ACTIVE_SKILL::Slow && mana > 1)
			{
				ResetSkillEffect();
				activeSkill = ACTIVE_SKILL::Slow;
				Director::getInstance()->getScheduler()->setTimeScale(0.5f);
				Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0.5f);

				this->addChild(CParticleLoader::createSlowEffect());

				CSoundLoader::playSoundEffect(CSoundLoader::DROPLET_SOUND_EFFECT);
			}
			else
			{
				ResetSkillEffect();
			}
		}
		break;
	}
}

void Player::ResetSkillEffect()
{
	activeSkill = ACTIVE_SKILL::None;
	GetSprite()->setOpacity(255);
	Director::getInstance()->getScheduler()->setTimeScale(1);
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1);
}

void Player::Move(bool right, float dt)
{
	isMoving = true;
	frictionLerpValue = 1;

	auto body = this->getPhysicsBody();

	if (right)
	{
		GetSprite()->setFlipX(false);
		body->applyImpulse(Vec2(body->getMass() * 1500.0f  * dt, 0));
	}
	else
	{
		GetSprite()->setFlipX(true);
		body->applyImpulse(Vec2(body->getMass() * -1500.0f  * dt, 0));
	}

	if (body->getVelocity().x > 200)
		body->setVelocity(Vec2(200, body->getVelocity().y));
	else if (body->getVelocity().x < -200)
		body->setVelocity(Vec2(-200, body->getVelocity().y));

	//body->getShapes().at(0)->setFriction(0);

	setA_Move();
}

void Player::Jump()
{
	if (jumpCount < maxJumpCount)
	{
		auto body = this->getPhysicsBody();

		body->setVelocity(Vec2(body->getVelocity().x, 0));
		body->applyImpulse(Vec2(0, this->getPhysicsBody()->getMass() * 400));
		jumpCount++;

		CSoundLoader::playSoundEffect(CSoundLoader::JUMP_SOUND_EFFECT);
	}
}

bool upKeypress = false;

void Player::Movement(float dt)
{
#if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC))
	if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
	{
		Move(false, dt);
	}
	if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		Move(true, dt);
	}
	if ((KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) && !upKeypress))
	{
		upKeypress = true;
		Jump();
	}
	else if (!KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) && upKeypress)
	{
		upKeypress = false;
	}
#elif ((CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
	if (moveLeft)
	{
		Move(false, dt);
	}
	if (moveRight)
	{
		Move(true, dt);
	}
#endif

	/*if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_S))
	{
		c->setPosition(c->getPositionX(), c->getPositionY() - dt * 500);
	}*/
}

void Player::ReceiveDamage(float fDamagingDuration)
{
	//auto body = this->getPhysicsBody();

	//body->setVelocity(Vec2(0, 0));
	//body->applyImpulse(dir * force * body->getMass());

	if (!isDamaged)
	{
		isDamaged = true;
		CGameObject::MinusLives(1);

		auto flickAction = CallFunc::create([this]()
		{
			this->setVisible(!this->isVisible());
		});
		float fTimeInterval = 0.1f;
		auto sequence = Sequence::createWithTwoActions(flickAction, DelayTime::create(fTimeInterval));
		auto repeat = Repeat::create(sequence, fDamagingDuration / fTimeInterval);
		auto checkAction = CallFunc::create([this]()
		{
			if (!this->isVisible())
				this->setVisible(true);
			isDamaged = false;
		});
		auto sequence2 = Sequence::createWithTwoActions(repeat, checkAction);
		this->runAction(sequence2);

		CParticleLoader::createBleedingEffect(this);

		CSoundLoader::playSoundEffect(CSoundLoader::JAB_SOUND_EFFECT);
	}
}

void Player::setA_Idle()
{
	if (astate != A_Idle)
	{
		GetSprite()->stopAllActions();

		astate = A_Idle;

	//Sprite::createWithTexture

		GetSprite()->setTexture(CSpriteLoader::getPlayerSprite(Size(50, 86))->getTexture());
		GetSprite()->setTextureRect(CSpriteLoader::getPlayerSprite(Size(50, 86))->getTextureRect());

		//SetSprite(CSpriteLoader::getPlayerSprite(), Size(49, 90));
	}
}

void Player::setA_Move()
{
	if (astate != A_Move)
	{
		auto sprite = GetSprite();
		sprite->stopAllActions();

		astate = A_Move;

		auto animate = RepeatForever::create(CAnimationLoader::getPlayerAnimate(astate, Size(62, 86), 0.1f));
		sprite->runAction(animate);
	}
}
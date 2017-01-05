#include "AIEnemy.h"
#include "Enemy.h"
#include "AnimationSystem.h"
#include "SpriteLoader.h"
#include "AnimationLoader.h"
#include "ParticleLoader.h"

USING_NS_CC;

CAIEnemy::CAIEnemy()
	: CAIBase()
	, m_pTargetGO(NULL)
	, m_fMovementSpeed(1.0f)
	, m_fAnimationSpeed(1.0f)
{
	m_sRanges.m_fDetectionRange = 0.0f;
	m_sRanges.m_fShootingRange = 0.0f;
	m_sRanges.m_fPouncingRange = 0.0f;
}

CAIEnemy::CAIEnemy(int nState, CGameObject* pGO)
	: CAIBase(nState, pGO)
	, m_pTargetGO(NULL)
	, m_fMovementSpeed(1.0f)
	, m_fAnimationSpeed(1.0f)
{
	m_sRanges.m_fDetectionRange = 0.0f;
	m_sRanges.m_fShootingRange = 0.0f;
	m_sRanges.m_fPouncingRange = 0.0f;
}

CAIEnemy::~CAIEnemy()
{
	CAIBase::~CAIBase();
}

void CAIEnemy::Init(CGameObject* pTargetGO, float fMovementSpeed, float fAnimationSpeed, ENEMY_RANGES sRanges)
{
	m_pTargetGO = pTargetGO;
	m_fMovementSpeed = fMovementSpeed;
	m_fAnimationSpeed = fAnimationSpeed;
	m_sRanges = sRanges;
}

void CAIEnemy::Update(float dt)
{
	CheckTarget();

	switch (m_nCurrentState)
	{
		case FSM_CHASE:
		{
			Vec2 targetPos(m_pTargetGO->getPositionX(), 0);
			Vec2 goPos(m_pGO->getPositionX(), 0);
			Vec2 thisToTarget(targetPos - goPos);
			Vec2 moveByCurrent = thisToTarget * dt / (targetPos.getDistance(goPos) / m_fMovementSpeed);
			m_pGO->runAction(MoveBy::create(dt, moveByCurrent));
			CheckDirection(moveByCurrent);
			break;
		}
		case FSM_SHOOT:
		{
			Shoot();
			break;
		}
		case FSM_POUNCE:
		{
			Pounce();
			break;
		}
	}
}

void CAIEnemy::Damaging(float fDamagingDuration)
{
	if (m_nCurrentState != FSM_DAMAGING && m_nCurrentState != FSM_DIED)
	{
		StopGO();

		m_nCurrentState = FSM_DAMAGING;


		auto flickAction = CallFunc::create([this]()
		{
			m_pGO->setVisible(!m_pGO->isVisible());
		});
		float fTimeInterval = 0.1f;
		auto sequence = Sequence::createWithTwoActions(flickAction, DelayTime::create(fTimeInterval));
		auto repeat = Repeat::create(sequence, fDamagingDuration / fTimeInterval);
		auto checkAction = CallFunc::create([this]()
		{
			if (!m_pGO->isVisible())
				m_pGO->setVisible(true);
			m_nCurrentState = FSM_IDLE;
		});
		auto sequence2 = Sequence::createWithTwoActions(repeat, checkAction);
		m_pGO->GetSprite()->runAction(sequence2);

		// Die if no live left
		if (m_pGO->GetLives() <= 0)
		{
			auto delayAction = DelayTime::create(fDamagingDuration);

			auto diedAction = CallFunc::create([this]()
			{
				StopGO();
				if (!m_pGO->isVisible())
					m_pGO->setVisible(true);
				m_nCurrentState = FSM_DIED;
			});
			m_pGO->runAction(Sequence::create(delayAction, diedAction, NULL));
		}
	}
}

void CAIEnemy::CheckTarget()
{
	if (m_nCurrentState != FSM_DAMAGING && m_nCurrentState != FSM_DIED)
	{
		if (m_pTargetGO)
		{
			float getDistance = m_pTargetGO->getPosition().getDistance(m_pGO->getPosition());

			if (getDistance <= m_sRanges.m_fPouncingRange)
			{
				Pounce();
				return;
			}
			else if (getDistance <= m_sRanges.m_fShootingRange)
			{
				Shoot();
				return;
			}
			else if (getDistance <= m_sRanges.m_fDetectionRange)
			{
				Chase();
				return;
			}
		}
		Idle();
	}
}
void CAIEnemy::CheckDirection(Vec2 moveByCurrent)
{
	auto sprite = m_pGO->GetSprite();
	if (moveByCurrent.x > 0 && !sprite->isFlippedX())
	{
		sprite->setFlippedX(true);
	}
	else if (moveByCurrent.x < 0 && sprite->isFlippedX())
	{
		sprite->setFlippedX(false);
	}
}

void CAIEnemy::StopGO()
{
	m_pGO->stopAllActions();
	auto sprite = m_pGO->GetSprite();
	if (sprite)
		sprite->stopAllActions();
	if (!m_pGO->getPhysicsBody()->isGravityEnabled())
		m_pGO->getPhysicsBody()->setGravityEnable(true);
}

void CAIEnemy::Idle()
{
	if (m_nCurrentState != FSM_IDLE)
	{
		StopGO();

		m_nCurrentState = FSM_IDLE;

		auto sprite = m_pGO->GetSprite();
		if (sprite)
		{
			auto animate = RepeatForever::create(CAnimationLoader::getEnemyAnimate(FSM_IDLE, dynamic_cast<CEnemy*>(m_pGO)->GetEnemeyType(), m_pGO->GetSpriteSize(), m_fAnimationSpeed));
			sprite->runAction(animate);
		}
	}
}

void CAIEnemy::Chase()
{
	if (m_nCurrentState != FSM_CHASE)
	{
		StopGO();

		m_nCurrentState = FSM_CHASE;

		auto sprite = m_pGO->GetSprite();
		if (sprite)
		{
			auto animate = RepeatForever::create(CAnimationLoader::getEnemyAnimate(FSM_CHASE, dynamic_cast<CEnemy*>(m_pGO)->GetEnemeyType(), m_pGO->GetSpriteSize(), m_fAnimationSpeed));
			sprite->runAction(animate);
		}
	}
}

void CAIEnemy::Shoot()
{
	if (m_nCurrentState != FSM_SHOOT)
	{
		StopGO();

		m_nCurrentState = FSM_SHOOT;
	}
	if (!m_pGO->getActionByTag(FSM_SHOOT))
	{
		// Set Projectile infomation
		auto projectile = CSpriteLoader::getProjectileSprites(m_shootingInfomations.m_fProjectileSize);
		projectile->setPosition(m_pGO->getPosition());
		projectile->setFlippedX(m_pGO->GetSprite()->isFlippedX());
		if (m_pGO->GetSprite()->isFlippedX())
		{
			projectile->setPositionX(m_pGO->getPositionX() + m_pGO->GetSpriteSize().width * 0.5f);
		}
		else
		{
			projectile->setPositionX(m_pGO->getPositionX() - m_pGO->GetSpriteSize().width * 0.5f);
		}
		m_pGO->getParent()->addChild(projectile);
		// Move the projectile
		auto vecMoveTo = m_pGO->getPosition() + (m_pTargetGO->getPosition() - m_pGO->getPosition()).getNormalized() * m_shootingInfomations.m_fEffectiveRange;
		MoveTo* moveBy = MoveTo::create(m_shootingInfomations.m_fEffectiveRange / m_shootingInfomations.m_fProjectileSpeed, vecMoveTo);
		auto destroyProjectile = RemoveSelf::create();

		auto sequence = Sequence::create(moveBy, destroyProjectile, NULL);
		sequence->setTag(FSM_SHOOT);
		projectile->runAction(sequence);

		auto coolDown = DelayTime::create(m_shootingInfomations.m_fFireRate);
		coolDown->setTag(FSM_SHOOT);
		m_pGO->runAction(coolDown);

		CheckDirection(-vecMoveTo);
	}
}

void CAIEnemy::Pounce()
{
	if (m_nCurrentState != FSM_POUNCE)
	{
		StopGO();

		m_nCurrentState = FSM_POUNCE;
	}
	if (!m_pGO->getActionByTag(FSM_POUNCE))
	{
		// Deactivate Gravity
		m_pGO->getPhysicsBody()->setGravityEnable(false);
		// Jump
		float distance = m_pTargetGO->getPosition().distance(m_pGO->getPosition());
		auto jumpAction = JumpTo::create(m_pounceInfomations.m_fPounceDuration, m_pTargetGO->getPosition(), m_pounceInfomations.m_fPounceHeight, 1);
		// Activate Gravity
		auto activateGravityAction = CallFunc::create([this]()
		{
			m_pGO->getPhysicsBody()->setGravityEnable(true);
		});
		// Cool Down
		auto coolDownAction = DelayTime::create(m_pounceInfomations.m_fCoolDownTIme);
		// Pounce Sequence
		auto pounceAction = Sequence::create(jumpAction, activateGravityAction, coolDownAction, NULL);
		pounceAction->setTag(FSM_POUNCE);
		m_pGO->runAction(pounceAction);

		CheckDirection(m_pTargetGO->getPosition() - m_pGO->getPosition());
	}
}
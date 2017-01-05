#include "AIEnemy.h"
#include "GameObject.h"
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

void CAIEnemy::Dying(float fTimeToDie)
{
	if (m_nCurrentState != FSM_DYING && m_nCurrentState != FSM_DIED)
	{
		StopGO();

		m_nCurrentState = FSM_DYING;

		auto dyingAction = DelayTime::create(fTimeToDie);
		auto diedAction = CallFunc::create([this]()
		{
			m_nCurrentState = FSM_DIED;
		});
		m_pGO->runAction(Sequence::create(dyingAction, diedAction, NULL));
	}
}

void CAIEnemy::CheckTarget()
{
	if (m_nCurrentState != FSM_DYING && m_nCurrentState != FSM_DIED)
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
			auto animate = RepeatForever::create(CAnimationLoader::getEnemyAnimate(FSM_IDLE, m_pGO->GetSpriteSize(), m_fAnimationSpeed));
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
			auto animate = RepeatForever::create(CAnimationLoader::getEnemyAnimate(FSM_CHASE, m_pGO->GetSpriteSize(), m_fAnimationSpeed));
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
		//sauto projectile = SpriteLoader
		//m_pGO->runAction();
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
	}
}
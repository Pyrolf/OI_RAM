#include "AIEnemy.h"
#include "GameObject.h"
#include "AnimationSystem.h"
#include "AnimationLoader.h"
#include "ParticleLoader.h"

USING_NS_CC;

CAIEnemy::CAIEnemy()
	: CAIBase()
	, m_pTargetGO(NULL)
	, m_fMovementSpeed(1.0f)
	, m_fAnimationSpeed(1.0f)
	, m_fDetectionRange(0.0f)
	, m_fAttackRange(0.0f)
{
}

CAIEnemy::CAIEnemy(int nState, CGameObject* pGO)
	: CAIBase(nState, pGO)
	, m_pTargetGO(NULL)
	, m_fMovementSpeed(1.0f)
	, m_fAnimationSpeed(1.0f)
	, m_fDetectionRange(0.0f)
	, m_fAttackRange(0.0f)
{
}

CAIEnemy::~CAIEnemy()
{
	CAIBase::~CAIBase();
}

void CAIEnemy::Init(CGameObject* pTargetGO, float fMovementSpeed, float fAnimationSpeed, float fDetectionRange, float fAttackRange)
{
	m_pTargetGO = pTargetGO;
	m_fMovementSpeed = fMovementSpeed;
	m_fAnimationSpeed = fAnimationSpeed;
	m_fDetectionRange = fDetectionRange;
	m_fAttackRange = fAttackRange;
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
		case FSM_ATTACK:
		{
			AttackOrDefend();
			break;
		}
		case FSM_DEFEND:
		{
			AttackOrDefend();
			break;
		}
	}
}

void CAIEnemy::Dying()
{
	if (m_nCurrentState != FSM_DYING && m_nCurrentState != FSM_DIED)
	{
		StopGO();

		m_nCurrentState = FSM_DYING;

		auto dyingAction = DelayTime::create(1.0f);
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

			if (getDistance <= m_fAttackRange)
			{
				AttackOrDefend();
				return;
			}
			else if (getDistance <= m_fDetectionRange)
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

void CAIEnemy::AttackOrDefend()
{
	if (m_nCurrentState != FSM_ATTACK ||
		m_nCurrentState != FSM_DEFEND)
	{
		if (RandomHelper::random_int(0, 1) == 0)
			Attack();
		else
			Defend();
	}
}
void CAIEnemy::Attack()
{
	StopGO();

	m_nCurrentState = FSM_ATTACK;
}

void CAIEnemy::Defend()
{
	StopGO();

	m_nCurrentState = FSM_DEFEND;
}

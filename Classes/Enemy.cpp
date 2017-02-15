#include "Enemy.h"
#include "AIEnemy.h"
#include "SoundLoader.h"

USING_NS_CC;

CEnemy::CEnemy()
	: CGameObject()
	, m_AI(NULL)
	, m_eEnemyType(ENEMY_TYPE_WEAK)
{
}

CEnemy::~CEnemy()
{
	if (m_AI)
		delete m_AI;
}

CEnemy* CEnemy::create()
{
	CEnemy * ret = new (std::nothrow) CEnemy();
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

void CEnemy::Init(ENEMY_TYPE eEnemyType, CGameObject* pTargetGO, float fMovementSpeed, float fAnimationSpeed, ENEMY_RANGES sRanges)
{
	m_AI = new CAIEnemy(CAIEnemy::FEM_NIL, this);
	m_eEnemyType = eEnemyType;
	m_AI->Init(pTargetGO, fMovementSpeed, fAnimationSpeed, sRanges);
}

void CEnemy::Update(float dt)
{
	if (m_AI)
		m_AI->Update(dt);
}

void CEnemy::MinusLives(int nDamage)
{
	if (m_AI->GetCurrentState() != CAIEnemy::FSM_DAMAGING && m_AI->GetCurrentState() != CAIEnemy::FSM_DIED)
	{
		CGameObject::MinusLives(nDamage);
		m_AI->Damaging();

		CSoundLoader::playSoundEffect(CSoundLoader::WHIP_SOUND_EFFECT);
	}
}
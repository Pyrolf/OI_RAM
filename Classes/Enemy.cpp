#include "Enemy.h"
#include "AIEnemy.h"

USING_NS_CC;

CEnemy::CEnemy()
	: CGameObject()
	, m_AI(NULL)
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

void CEnemy::Init(CGameObject* pTargetGO, float speed, float fDetectionRange, float fAttackRange)
{
	m_AI = new CAIEnemy(CAIEnemy::FEM_NIL, this);
	m_AI->Init(pTargetGO, speed, fDetectionRange, fAttackRange);
}

void CEnemy::Update(float dt)
{
	if (m_AI)
		m_AI->Update(dt);
}
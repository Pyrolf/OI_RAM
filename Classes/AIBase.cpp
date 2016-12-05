#include "AIBase.h"
#include "GameObject.h"

USING_NS_CC;

CAIBase::CAIBase()
	: m_nCurrentState(0)
	, m_pGO(NULL)
{
}

CAIBase::CAIBase(int nState, CGameObject* pGO)
	: m_nCurrentState(nState)
	, m_pGO(pGO)
{
}

CAIBase::~CAIBase()
{
}
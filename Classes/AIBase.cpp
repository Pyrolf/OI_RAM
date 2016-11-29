#include "AIBase.h"

CAIBase::CAIBase()
	: m_nCurrentState(0)
	, m_pGO(NULL)
{
}

CAIBase::CAIBase(int nState, cocos2d::Node* pGO)
	: m_nCurrentState(nState)
	, m_pGO(pGO)
{
}

CAIBase::~CAIBase()
{
	if (m_pGO)
		delete m_pGO;
}
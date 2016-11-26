#include "AIEnemy.h"

CAIEnemy::CAIEnemy()
{
}

CAIEnemy::~CAIEnemy()
{
	if (m_pGO)
		delete m_pGO;
}
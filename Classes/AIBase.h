#ifndef __AI_BASE_H__
#define __AI_BASE_H__

class CGameObject;

#include "cocos2d.h"

class CAIBase
{
protected:
	int m_nCurrentState;
	CGameObject* m_pGO;
public:
	CAIBase();
	CAIBase(int nState, CGameObject* pGO);
	~CAIBase();

	virtual void Update(float dt) = 0;

	// Getters
	int GetCurrentState(){ return m_nCurrentState; }
	CGameObject* GetGameObject(){ return m_pGO; }
};

#endif // __AI_BASE_H__

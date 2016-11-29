#ifndef __AI_BASE_H__
#define __AI_BASE_H__

#include "cocos2d.h"

class CAIBase
{
protected:
	int m_nCurrentState;
	cocos2d::Node* m_pGO;
public:
	CAIBase();
	CAIBase(int nState, cocos2d::Node* pGO);
	~CAIBase();

	virtual void Update(float dt) = 0;

	// Getters
	int GetCurrentState(){ return m_nCurrentState; }
	cocos2d::Node* GetGameObject(){ return m_pGO; }
};

#endif // __AI_BASE_H__

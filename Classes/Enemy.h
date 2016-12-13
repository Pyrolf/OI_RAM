#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "AIEnemy.h"
#include "GameObject.h"

class CEnemy : public CGameObject
{
public:
	CEnemy();
	virtual ~CEnemy();

	static CEnemy* create();

	void Init(CGameObject* pTargetGO, float fMovementSpeed, float fAnimationSpeed, float fDetectionRange, float fAttackRange);
	void Update(float dt);

	// Setters
	void SetTarget(CAIEnemy* ai) { m_AI = ai; }
	// Getters
	CAIEnemy* GetAI() { return m_AI; }
private:
	CAIEnemy* m_AI;
};

#endif // __ENEMY_H__
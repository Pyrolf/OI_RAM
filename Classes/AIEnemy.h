#ifndef __AI_ENEMY_H__
#define __AI_ENEMY_H__

#include "AIBase.h"

class CAIEnemy : public CAIBase
{
private:
	CGameObject* m_pTargetGO;
	float m_fSpeed;
	float m_fDetectionRange;
	float m_fAttackRange;
public:
	CAIEnemy();
	CAIEnemy(int nState, CGameObject* pGO);
	~CAIEnemy();

	enum FSM
	{
		FEM_NIL = 0,
		FSM_IDLE,
		FSM_CHASE,
		FSM_ATTACK,
		FSM_DEFEND,
		FSM_DYING,
		FSM_DIED,
		NUM_OF_STATES
	};

	void Init(CGameObject* pTargetGO, float speed, float fDetectionRange, float fAttackRange);
	virtual void Update(float dt);

	void Dying();

	// Setters
	void SetSpeed(float speed) { m_fSpeed = speed; }
	void SetTarget(CGameObject* pTargetGO) { m_pTargetGO = pTargetGO; }
	// Getters
	float GetSpeed() { return m_fSpeed; }
	CGameObject* GetTarget() { return m_pTargetGO; }

private:
	void CheckTarget();

	void StopGO();

	void Idle();
	void Chase();
	void AttackOrDefend();
	void Attack();
	void Defend();
};

#endif // __AI_ENEMY_H__

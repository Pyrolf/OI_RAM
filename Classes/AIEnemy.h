#ifndef __AI_ENEMY_H__
#define __AI_ENEMY_H__

#include "AIBase.h"

class CAIEnemy : public CAIBase
{
private:
	CGameObject* m_pTargetGO;
	float m_fMovementSpeed;
	float m_fAnimationSpeed;
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

	void Init(CGameObject* pTargetGO, float fMovementSpeed, float fAnimationSpeed, float fDetectionRange, float fAttackRange);
	virtual void Update(float dt);

	void Dying();

	// Setters
	void SetMovementSpeed(float fMovementSpeed) { m_fMovementSpeed = fMovementSpeed; }
	void SetAnimationSpeed(float fAnimationSpeed) { m_fAnimationSpeed = fAnimationSpeed; }
	void SetTarget(CGameObject* pTargetGO) { m_pTargetGO = pTargetGO; }
	// Getters
	float GetMovementSpeed() { return m_fMovementSpeed; }
	float GtAnimationSpeed() { return m_fAnimationSpeed; }
	CGameObject* GetTarget() { return m_pTargetGO; }

private:
	void CheckTarget();
	void CheckDirection(cocos2d::Vec2 moveByCurrent);

	void StopGO();

	void Idle();
	void Chase();
	void AttackOrDefend();
	void Attack();
	void Defend();
};

#endif // __AI_ENEMY_H__

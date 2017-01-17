#ifndef __AI_ENEMY_H__
#define __AI_ENEMY_H__

#include "AIBase.h"

struct ENEMY_RANGES
{
	float m_fDetectionRange;
	float m_fShootingRange;
	float m_fPouncingRange;
};

class CAIEnemy : public CAIBase
{
private:
	CGameObject* m_pTargetGO;
	float m_fMovementSpeed;
	float m_fAnimationSpeed;
	ENEMY_RANGES m_sRanges;

	// Shooting information
	struct ShootingInformations
	{
		float m_fFireRate = 0;
		cocos2d::Size m_fProjectileSize = cocos2d::Size(0, 0);
		float m_fProjectileSpeed = 0;
		float m_fEffectiveRange = 0;
	};
	ShootingInformations m_shootingInfomations;

	// Pounce information
	struct PounceInformations
	{
		float m_fPounceDuration = 0;
		float m_fPounceHeight = 0;
		float m_fCoolDownTIme = 0;
	};
	PounceInformations m_pounceInfomations;
public:
	CAIEnemy();
	CAIEnemy(int nState, CGameObject* pGO);
	~CAIEnemy();

	enum FSM
	{
		FEM_NIL = 0,
		FSM_IDLE,
		FSM_CHASE,
		FSM_SHOOT,
		FSM_POUNCE,
		FSM_DAMAGING,
		FSM_DIED,
		NUM_OF_STATES
	};

	void Init(CGameObject* pTargetGO, float fMovementSpeed, float fAnimationSpeed, ENEMY_RANGES sRanges);
	virtual void Update(float dt);

	void Damaging(float fDamagingDuration = 1.0f);
	void PounceCoolDown();

	// Setters
	void SetMovementSpeed(float fMovementSpeed) { m_fMovementSpeed = fMovementSpeed; }
	void SetAnimationSpeed(float fAnimationSpeed) { m_fAnimationSpeed = fAnimationSpeed; }
	void SetTarget(CGameObject* pTargetGO) { m_pTargetGO = pTargetGO; }
	void SetShootingInfomations(float fFireRate = 0, cocos2d::Size fProjectileSize = cocos2d::Size(0, 0), float fProjectileSpeed = 0, float fEffectiveRange = 0)
	{
		m_shootingInfomations.m_fFireRate = fFireRate;
		m_shootingInfomations.m_fProjectileSize = fProjectileSize;
		m_shootingInfomations.m_fProjectileSpeed = fProjectileSpeed;
		m_shootingInfomations.m_fEffectiveRange = fEffectiveRange;
	}
	void SetPounceInfomations(float fPounceDuration = 0, float fPounceHeight = 0, float fCoolDownTIme = 0)
	{
		m_pounceInfomations.m_fPounceDuration = fPounceDuration;
		m_pounceInfomations.m_fPounceHeight = fPounceHeight;
		m_pounceInfomations.m_fCoolDownTIme = fCoolDownTIme;
	}
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
	void Shoot();
	void Pounce();
};

#endif // __AI_ENEMY_H__

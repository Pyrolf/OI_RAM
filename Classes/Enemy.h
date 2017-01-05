#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "AIEnemy.h"
#include "GameObject.h"

class CEnemy : public CGameObject
{
public:
	CEnemy();
	virtual ~CEnemy();

	enum ENEMY_TYPE
	{
		ENEMY_TYPE_WEAK = 0,
		ENEMY_TYPE_STRONG,
		ENEMY_TYPE_POUNCER,
		ENEMY_TYPE_SHOOTER,
		ENEMY_TYPE_HYBRID,
		NUM_OF_ENEMY_TYPES
	};

	static CEnemy* create();

	void Init(ENEMY_TYPE eEnemyType, CGameObject* pTargetGO, float fMovementSpeed, float fAnimationSpeed, ENEMY_RANGES sRanges);
	void Update(float dt);

	// Setters
	void SetTarget(CAIEnemy* ai) { m_AI = ai; }
	// Getters
	CAIEnemy* GetAI() { return m_AI; }
	ENEMY_TYPE GetEnemeyType() { return m_eEnemyType; }
private:
	CAIEnemy* m_AI;
	ENEMY_TYPE m_eEnemyType;
};

#endif // __ENEMY_H__
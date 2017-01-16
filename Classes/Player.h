#pragma once

#include "cocos2d.h"
#include "GameObject.h"

using namespace cocos2d;

#define GROUND_FRICTION_MULTI 1
#define AIR_FRICTION_MULTI 0.1

class Player : public CGameObject
{
public:
	enum A_STATE
	{
		A_Idle,
		A_Move
	};

	enum ACTIVE_SKILL
	{
		None,
		Slam,
		Slow,
		Invisible
	};

	Player();
	virtual ~Player();

	void Init(Vec2 Pos);
	virtual void Update(float dt);

	void UpdateSkills(float dt);

	ACTIVE_SKILL GetActiveSkill() { return activeSkill; };
	void ResetSkillEffect();

	void Movement(float dt);
	void Move(bool right, float dt);
	void Jump();

	void SetJumpCount(int i) { jumpCount = i; };
	void SetFrictionMulti(float f) { frictionMulti = f; };

	void ReceiveDamage(float fDamagingDuration = 1);


	void setMana(float m) {
		mana = m; 
		if (mana > maxMana)
			mana = maxMana; };

	float getMana() { return mana; };
	float getMaxMana() { return maxMana; };

private:
	A_STATE astate;

	ACTIVE_SKILL activeSkill;
	float slamSkillActiveTime = 0;

	bool isMoving = false;
	float frictionMulti = 0;
	float frictionLerpValue = 0;

	bool isDamaged = false;

	int jumpCount = 0;
	int maxJumpCount = 2;

	float mana;
	float maxMana;
	float manaRegenRate;

	void setA_Idle();

	void setA_Move();
};
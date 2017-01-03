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

	Player();
	virtual ~Player();

	void Init(Vec2 Pos);
	virtual void update(float);

	void Movement(float dt);
	void Move(bool right, float dt);
	void Jump();

	void SetJumpCount(int i) { jumpCount = i; };
	void SetFrictionMulti(float f) { frictionMulti = f; };

	void Knockback(Vec2 dir, float force);
private:
	A_STATE astate;

	bool isMoving = false;
	float frictionMulti = 0;
	float frictionLerpValue = 0;

	int jumpCount = 0;
	int maxJumpCount = 2;

	void setA_Idle();

	void setA_Move();
};
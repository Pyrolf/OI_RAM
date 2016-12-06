#pragma once

#include "cocos2d.h"

using namespace cocos2d;

#define GROUND_FRICTION_MULTI 1
#define AIR_FRICTION_MULTI 0.1

class Player : public cocos2d::Node
{
public:

	Player();
	~Player();

	virtual void update(float);

	void Move(bool right, float speed, float dt);
	void Jump();

	void SetJumpCount(int i) { jumpCount = i; };
	void SetFrictionMulti(float f) { frictionMulti = f; };
private:
	Sprite* sprite;

	bool isMoving = false;
	float frictionMulti = 0;
	float frictionLerpValue = 0;

	int jumpCount = 0;
	int maxJumpCount = 2;
	//Node* playerTop, *playerBottom;
};
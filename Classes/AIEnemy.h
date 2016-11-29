#ifndef __AI_ENEMY_H__
#define __AI_ENEMY_H__

#include "AIBase.h"

class CAIEnemy : public CAIBase
{
public:
	CAIEnemy();
	~CAIEnemy();

	enum FSM
	{
		IDLE = 0,
		ATTACK,
		CHASE,
		DEFEND,
		NUM_OF_STATES
	};

	virtual void Update(float dt) = 0;
};

#endif // __AI_ENEMY_H__

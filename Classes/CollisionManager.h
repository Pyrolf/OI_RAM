#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

#include "cocos2d.h"

class CCollisionManager : public cocos2d::Node
{
public:
	
	enum COLLISION_BITMASK
	{
		CB_PLAYER = 1,
		CB_GROUND,
		CB_ENEMY
	};

	CCollisionManager();
	~CCollisionManager();

	void Update(float dt);
private:

	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onContactSeparate(cocos2d::PhysicsContact& contact);
	//bool onContactPreSolve(cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve);
};

#endif // __COLLISION_MANAGER_H__

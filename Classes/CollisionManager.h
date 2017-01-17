#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

#include "cocos2d.h"
#include "Enemy.h"

class CCollisionManager : public cocos2d::Node
{
public:
	
	enum COLLISION_BITMASK
	{
		CB_PLAYER = 1,
		CB_GROUND,
		CB_ENEMY,
		CB_ENEMY_BULLET,
		CB_CRATE,
		CB_JUMPAD
	};

	CCollisionManager();
	~CCollisionManager();

	void Update(float dt);

	static void addPhysicBody(CEnemy* target);
	static void addPhysicBodyEnemyBullet(cocos2d::Sprite* target);

private:

	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onContactSeparate(cocos2d::PhysicsContact& contact);
	//bool onContactPreSolve(cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve);
};

#endif // __COLLISION_MANAGER_H__

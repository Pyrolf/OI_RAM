#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

#include "cocos2d.h"

class CCollisionManager
{
public:
	CCollisionManager();
	~CCollisionManager();

	void Update(float dt);
private:

	void CheckForCollision(cocos2d::Node* pGO1, cocos2d::Node* pGO2);
};

#endif // __COLLISION_MANAGER_H__

#include "CollisionManager.h"

USING_NS_CC;

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Update(float dt)
{
}

void CCollisionManager::CheckForCollision(Node* pGO1, Node* pGO2)
{
	if (pGO1->getBoundingBox().intersectsRect(pGO2->getBoundingBox()))
	{
		// Handle collision
	}
}
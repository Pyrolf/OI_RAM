#ifndef __GAME_OBJECT_MANAGER_H__
#define __GAME_OBJECT_MANAGER_H__

#include "Enemy.h"

class CGameObjectManager : cocos2d::Node
{
public:
	CGameObjectManager(int numOfEnemies, cocos2d::Size enemySpriteSize);
	~CGameObjectManager();

	static CGameObjectManager* create(int numOfEnemies, cocos2d::Size enemySpriteSize);

	void Update(float dt);

	void SpawnEnemy(cocos2d::Vec2 vec2Position,
					CGameObject* pTargetGO, float speed, float fDetectionRange, float fAttackRange);
	// Getters
	cocos2d::Size GetEnemySpriteSize() { return m_EnemySpriteSize; }
private:
	cocos2d::Layer* m_pLayer;
	int m_nAmountOfEnemiesToAdd;
	cocos2d::Vector<CEnemy*> m_pEnemyList;
	cocos2d::Size m_EnemySpriteSize;

	void AddEnemies(int numOfEnemies);
	CEnemy* GetAnInactiveEnemy();
	void DeactivateEnemy(CEnemy* enemy);
};


#endif // __GAME_OBJECT_MANAGER_H__
#ifndef __GAME_OBJECT_MANAGER_H__
#define __GAME_OBJECT_MANAGER_H__

#include "Enemy.h"
#include "Player.h"

class CGameObjectManager : cocos2d::Node
{
public:
	CGameObjectManager(int numOfEnemies);
	~CGameObjectManager();

	static CGameObjectManager* create(int numOfEnemies);

	void Update(float dt);

	void SpawnEnemy(cocos2d::Vec2 vec2Position,
					CGameObject* pTargetGO, float speed, float fDetectionRange, float fAttackRange);
	// Getters
	cocos2d::Size GetEnemySpriteSize() { return m_EnemySpriteSize; }

	void SpawnPlayer(cocos2d::Vec2 Pos);

	Player* getPlayer() { return dynamic_cast<Player*>(m_pLayerGO); };
private:
	CGameObject* m_pLayerGO = NULL;

	int m_nAmountOfEnemiesToAdd;
	cocos2d::Vector<CEnemy*> m_pEnemyList;
	cocos2d::Size m_EnemySpriteSize;

	void AddEnemies(int numOfEnemies);
	CEnemy* GetAnInactiveEnemy();
	void DeactivateEnemy(CEnemy* enemy);
};


#endif // __GAME_OBJECT_MANAGER_H__
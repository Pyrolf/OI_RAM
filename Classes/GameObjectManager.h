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

	void SetEnemyInfomations();
	void SpawnEnemy(cocos2d::Vec2 vec2Position, CEnemy::ENEMY_TYPE eEnemyType);
	// Getters
	cocos2d::Size GetEnemySpriteSize(CEnemy::ENEMY_TYPE type) { 
		if (type != CEnemy::NUM_OF_ENEMY_TYPES)
			return m_arrayOfEnemySpriteSizes[type];
	}

	void SpawnPlayer(cocos2d::Vec2 Pos);

	Player* getPlayer() { return dynamic_cast<Player*>(m_pLayerGO); };
private:
	CGameObject* m_pLayerGO = NULL;

	int m_nAmountOfEnemiesToAdd;
	cocos2d::Vector<CEnemy*> m_pEnemyList;
	cocos2d::Size m_arrayOfEnemySpriteSizes[CEnemy::NUM_OF_ENEMY_TYPES];
	int m_arrayOfEnemyLives[CEnemy::NUM_OF_ENEMY_TYPES];
	float m_arrayOfEnemyMovementSpeed[CEnemy::NUM_OF_ENEMY_TYPES];
	float m_arrayOfEnemyAnimationSpeed[CEnemy::NUM_OF_ENEMY_TYPES];
	ENEMY_RANGES m_arrayOfEnemyRanges[CEnemy::NUM_OF_ENEMY_TYPES];

	void AddEnemies(int numOfEnemies);
	CEnemy* GetAnInactiveEnemy();
	void DeactivateEnemy(CEnemy* enemy);

	cocos2d::Size m_ProjectileSpriteSize;
};


#endif // __GAME_OBJECT_MANAGER_H__
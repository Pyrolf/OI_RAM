#ifndef __GAME_OBJECT_MANAGER_H__
#define __GAME_OBJECT_MANAGER_H__

#include "Enemy.h"
#include "Player.h"
#include "InteractableGameObject.h"
#include "PhysicsGameObject.h"

class CGameObjectManager : public cocos2d::Node
{
public:
	CGameObjectManager(int numOfEnemies, int numOfIteractableItems, int numOfPhysicsGO);
	~CGameObjectManager();

	static CGameObjectManager* create(int numOfEnemies = 10, int numOfIteractableItems = 10, int numOfPhysicsGO = 10);

	void Update(float dt);

	void SetEnemyInfomations();
	void SpawnEnemy(cocos2d::Vec2 vec2Position, CEnemy::ENEMY_TYPE eEnemyType);

	void SpawnInteractableItem(cocos2d::Vec2 vec2Position, CInteractableGameObject::TYPE eInteractableItemType);

	void SpawnPhysicsGO(cocos2d::Vec2 vec2Position, CPhysicsGameObject::TYPE PhysicsGOType);

	// Getters
	cocos2d::Size GetEnemySpriteSize(CEnemy::ENEMY_TYPE type) { 
		if (type != CEnemy::NUM_OF_ENEMY_TYPES)
			return m_arrayOfEnemySpriteSizes[type];
	}

	void SpawnPlayer(cocos2d::Vec2 Pos);

	Player* getPlayer() { return dynamic_cast<Player*>(m_pLayerGO); };
private:
	CGameObject* m_pLayerGO = NULL;

	// Enemies
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

	// Projectile
	cocos2d::Size m_ProjectileSpriteSize;

	// Interactable items
	int m_nAmountOfInteractableItemsToAdd;
	cocos2d::Vector<CInteractableGameObject*> m_pInteractableItemsList;

	cocos2d::Size m_arrayOfInteractableItemSizes[CInteractableGameObject::NUM_OF_TYPES];

	void AddInteractableItems(int numOfInteractableItems);
	CInteractableGameObject* GetAnInactiveInteractableItem();
	void DeactivateInteractableItem(CInteractableGameObject* item);

	// Physics Object
	int m_nAmountOfPhysicsGOToAdd;
	cocos2d::Vector<CPhysicsGameObject*> m_pPhysicsGOList;

	cocos2d::Size m_arrayOfPhysicsGOSizes[CPhysicsGameObject::NUM_OF_TYPES];

	void AddPhysicsGO(int numOfPhysicsGO);
	CPhysicsGameObject* GetAnInactivePhysicsGO();
	void DeactivatePhysicsGO(CPhysicsGameObject* item);
};


#endif // __GAME_OBJECT_MANAGER_H__
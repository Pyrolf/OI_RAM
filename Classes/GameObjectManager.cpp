#include "GameObjectManager.h"
#include "Enemy.h"
#include "SpriteLoader.h"
#include "AnimationLoader.h"
#include "CollisionManager.h"
#include "InGameScene.h"
#include "SoundLoader.h"

USING_NS_CC;

CGameObjectManager::CGameObjectManager(int numOfEnemies, int numOfIteractableItems, int numOfPhysicsGO)
	: m_nAmountOfEnemiesToAdd(numOfEnemies)
	, m_nAmountOfInteractableItemsToAdd(numOfIteractableItems)
	, m_nAmountOfPhysicsGOToAdd(numOfPhysicsGO)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// Set Size
	m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_WEAK]		= Size(visibleSize.width * 0.1f, visibleSize.height * 0.1f);
	m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_STRONG]	= Size(visibleSize.width * 0.11f, visibleSize.height * 0.125f);
	m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_POUNCER]	= Size(visibleSize.width * 0.11f, visibleSize.height * 0.11f);
	m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_SHOOTER]	= Size(visibleSize.width * 0.1f, visibleSize.height * 0.11f);
	m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_HYBRID]	= Size(visibleSize.width * 0.125f, visibleSize.height * 0.15f);

	m_ProjectileSpriteSize = Size(visibleSize.height * 0.05f, visibleSize.height * 0.05f);
	
	m_arrayOfInteractableItemSizes[CInteractableGameObject::COIN]			= Size(visibleSize.height * 0.1f, visibleSize.height * 0.1f);
	m_arrayOfInteractableItemSizes[CInteractableGameObject::LIVE]			= Size(visibleSize.height * 0.1f, visibleSize.height * 0.1f);
	m_arrayOfInteractableItemSizes[CInteractableGameObject::MANA_POTION]	= Size(visibleSize.height * 0.1f, visibleSize.height * 0.1f);
	m_arrayOfInteractableItemSizes[CInteractableGameObject::EXIT]			= Size(visibleSize.height * 0.15f, visibleSize.height * 0.05f);

	m_arrayOfPhysicsGOSizes[CPhysicsGameObject::CRATE] = Size(visibleSize.height * 0.1f, visibleSize.height * 0.1f);
	m_arrayOfPhysicsGOSizes[CPhysicsGameObject::JUMPPAD] = Size(visibleSize.height * 0.1f, visibleSize.height * 0.025f);
	// Set Lives
	m_arrayOfEnemyLives[CEnemy::ENEMY_TYPE_WEAK]	= 1;
	m_arrayOfEnemyLives[CEnemy::ENEMY_TYPE_STRONG]	= 3;
	m_arrayOfEnemyLives[CEnemy::ENEMY_TYPE_POUNCER]	= 2;
	m_arrayOfEnemyLives[CEnemy::ENEMY_TYPE_SHOOTER]	= 1;
	m_arrayOfEnemyLives[CEnemy::ENEMY_TYPE_HYBRID]	= 5;
	// Set Movement Speed
	m_arrayOfEnemyMovementSpeed[CEnemy::ENEMY_TYPE_WEAK]	= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_WEAK].width * 0.75f;
	m_arrayOfEnemyMovementSpeed[CEnemy::ENEMY_TYPE_STRONG]	= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_STRONG].width * 0.75f;
	m_arrayOfEnemyMovementSpeed[CEnemy::ENEMY_TYPE_POUNCER] = m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_POUNCER].width * 0.75f;
	m_arrayOfEnemyMovementSpeed[CEnemy::ENEMY_TYPE_SHOOTER] = m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_SHOOTER].width * 0.75f;
	m_arrayOfEnemyMovementSpeed[CEnemy::ENEMY_TYPE_HYBRID]	= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_HYBRID].width * 0.75f;
	// Set Animation Speed
	m_arrayOfEnemyAnimationSpeed[CEnemy::ENEMY_TYPE_WEAK]		= 1 / m_arrayOfEnemyMovementSpeed[CEnemy::ENEMY_TYPE_WEAK] * 10.0f;
	m_arrayOfEnemyAnimationSpeed[CEnemy::ENEMY_TYPE_STRONG]		= 1 / m_arrayOfEnemyMovementSpeed[CEnemy::ENEMY_TYPE_STRONG] * 10.0f;
	m_arrayOfEnemyAnimationSpeed[CEnemy::ENEMY_TYPE_POUNCER]	= 1 / m_arrayOfEnemyMovementSpeed[CEnemy::ENEMY_TYPE_POUNCER] * 10.0f;
	m_arrayOfEnemyAnimationSpeed[CEnemy::ENEMY_TYPE_SHOOTER]	= 1 / m_arrayOfEnemyMovementSpeed[CEnemy::ENEMY_TYPE_SHOOTER] * 10.0f;
	m_arrayOfEnemyAnimationSpeed[CEnemy::ENEMY_TYPE_HYBRID]		= 1 / m_arrayOfEnemyMovementSpeed[CEnemy::ENEMY_TYPE_HYBRID] * 10.0f;
	// Set Ranges
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_WEAK].m_fDetectionRange		= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_WEAK].width * 3.0f;
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_WEAK].m_fShootingRange		= 0.0f;
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_WEAK].m_fPouncingRange		= 0.0f;
	
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_STRONG].m_fDetectionRange	= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_STRONG].width * 3.0f;
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_STRONG].m_fShootingRange	= 0.0f;
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_STRONG].m_fPouncingRange	= 0.0f;
	
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_POUNCER].m_fDetectionRange	= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_POUNCER].width * 3.0f;
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_POUNCER].m_fShootingRange	= 0.0f;
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_POUNCER].m_fPouncingRange	= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_POUNCER].width * 2.0f;
	
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_SHOOTER].m_fDetectionRange	= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_SHOOTER].width * 3.0f;
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_SHOOTER].m_fShootingRange	= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_SHOOTER].width * 2.0f;
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_SHOOTER].m_fPouncingRange	= 0.0f;
	
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_HYBRID].m_fDetectionRange	= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_HYBRID].width * 3.0f;
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_HYBRID].m_fShootingRange	= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_HYBRID].width * 2.5f;
	m_arrayOfEnemyRanges[CEnemy::ENEMY_TYPE_HYBRID].m_fPouncingRange	= m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_HYBRID].width * 2.0f;

	// Load Sprites and Animations
	for (int i = 0; i < CEnemy::NUM_OF_ENEMY_TYPES; i++)
	{
		CSpriteLoader::loadEnemySprites((CEnemy::ENEMY_TYPE)i, m_arrayOfEnemySpriteSizes[i]);
		CAnimationLoader::loadEnemiesAnimates((CEnemy::ENEMY_TYPE)i, m_arrayOfEnemySpriteSizes[i]);
	}
	CSpriteLoader::loadProjectileSprites(m_ProjectileSpriteSize);
	for (int i = 0; i < CInteractableGameObject::NUM_OF_TYPES; i++)
	{
		CSpriteLoader::loadInteractiveItemSprites((CInteractableGameObject::TYPE)i, m_arrayOfInteractableItemSizes[i]);
	}
	CSpriteLoader::loadPlayerSprites(Size(50, 86));
	CAnimationLoader::loadPlayerAnimates(Size(62, 86));

	AddEnemies(numOfEnemies);
}


CGameObjectManager::~CGameObjectManager()
{
}


CGameObjectManager* CGameObjectManager::create(int numOfEnemies, int numOfIteractableItems, int numOfPhysicsGO)
{
	CGameObjectManager * ret = new (std::nothrow) CGameObjectManager(numOfEnemies, numOfIteractableItems, numOfPhysicsGO);
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void CGameObjectManager::Update(float dt)
{
	for (int i = 0; i < m_pEnemyList.size(); i++)
	{
		auto enemy = m_pEnemyList.at(i);
		if (enemy->GetActive())
		{
			enemy->Update(dt);
			if (enemy->GetAI()->GetCurrentState() == CAIEnemy::FSM_DIED)
			{
				DeactivateEnemy(enemy);
			}
		}
	}

	for (int i = 0; i < m_pInteractableItemsList.size(); i++)
	{
		auto item = m_pInteractableItemsList.at(i);
		if (item->GetActive())
		{
			if (item->CheckCollision())
			{
				switch (item->GetType())
				{
					case CInteractableGameObject::COIN:
						((CInGameScene*)this->getParent())->AddCoins(1);
						break;
					case CInteractableGameObject::LIVE:
						((CInGameScene*)this->getParent())->AddLives(1);
						break;
					case CInteractableGameObject::MANA_POTION:
						((CInGameScene*)this->getParent())->AddMana(20);
						break;
					case CInteractableGameObject::EXIT:
						((CInGameScene*)this->getParent())->ReachExit();
						break;
				}
				DeactivateInteractableItem(item);
				CSoundLoader::playSoundEffect(CSoundLoader::CHIME_SOUND_EFFECT);
			}
		}
	}
}

void CGameObjectManager::SpawnEnemy(Vec2 vec2Position, CEnemy::ENEMY_TYPE eEnemyType)
{
	auto enemy = GetAnInactiveEnemy();
	enemy->SetActive(true);
	enemy->SetSprite(CSpriteLoader::getEnemySprite(eEnemyType, m_arrayOfEnemySpriteSizes[eEnemyType]), m_arrayOfEnemySpriteSizes[eEnemyType]);
	CCollisionManager::addPhysicBody(enemy);
	enemy->setPosition(vec2Position);
	enemy->Init(eEnemyType, m_pLayerGO, m_arrayOfEnemyMovementSpeed[eEnemyType], m_arrayOfEnemyAnimationSpeed[eEnemyType], m_arrayOfEnemyRanges[eEnemyType]);
	enemy->SetLives(m_arrayOfEnemyLives[eEnemyType]);
	CAIEnemy* aiEnmey =	enemy->GetAI();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	switch (eEnemyType)
	{
		case CEnemy::ENEMY_TYPE_WEAK:
		{
			enemy->GetSprite()->setColor(Color3B::WHITE);
			break;
		}
		case CEnemy::ENEMY_TYPE_STRONG:
		{
			enemy->GetSprite()->setColor(Color3B::YELLOW);
			break;
		}
		case CEnemy::ENEMY_TYPE_SHOOTER:
		{
			enemy->GetSprite()->setColor(Color3B::GREEN);
			aiEnmey->SetShootingInfomations(2.0f, m_ProjectileSpriteSize, 200.0f, visibleSize.width * 0.3f);
			break;
		}
		case CEnemy::ENEMY_TYPE_POUNCER:
		{
			enemy->GetSprite()->setColor(Color3B::RED);
			aiEnmey->SetPounceInfomations(0.75f, m_arrayOfEnemySpriteSizes[eEnemyType].height * 0.5f, 2.0f);
			break;
		}
		case CEnemy::ENEMY_TYPE_HYBRID:
		{
			enemy->GetSprite()->setColor(Color3B::MAGENTA);
			aiEnmey->SetPounceInfomations(0.75f, m_arrayOfEnemySpriteSizes[eEnemyType].height * 0.5f, 2.0f);
			aiEnmey->SetShootingInfomations(2.0f, m_ProjectileSpriteSize, 200.0f, visibleSize.width * 0.3f);
			break;
		}
	}
}

void CGameObjectManager::AddEnemies(int numOfEnemies)
{
	int goListSize = m_pEnemyList.size();
	for (int i = 0; i < numOfEnemies; i++)
	{
		auto enemy = CEnemy::create();
		DeactivateEnemy(enemy);
		enemy->setTag(goListSize + i);
		m_pEnemyList.pushBack(enemy);
		this->addChild(enemy);
	}
}

CEnemy* CGameObjectManager::GetAnInactiveEnemy()
{
	// Find an inactive enemy
	for (int i = 0; i < m_pEnemyList.size(); i++)
	{
		CEnemy* enemy = m_pEnemyList.at(i);
		if (!enemy->GetActive())
		{
			enemy->resume();
			enemy->setVisible(true);
			return enemy;
		}
	}
	// Create more game objects if no empty game object
	AddEnemies(m_nAmountOfEnemiesToAdd);
	return GetAnInactiveEnemy();
}

void CGameObjectManager::SpawnPlayer(Vec2 Pos)
{
	if (m_pLayerGO == NULL)
		m_pLayerGO = new Player();

	m_pLayerGO->SetActive(true);
	m_pLayerGO->removeFromParent();
	this->addChild(m_pLayerGO);
	dynamic_cast<Player*>(this->m_pLayerGO)->Init(Pos);
}


void CGameObjectManager::DeactivateEnemy(CEnemy* enemy)
{
	if (enemy->getPhysicsBody())
		enemy->getPhysicsBody()->setEnabled(false);
	enemy->SetActive(false);
	enemy->pause();
	enemy->setVisible(false);
}


void CGameObjectManager::SpawnInteractableItem(cocos2d::Vec2 vec2Position, CInteractableGameObject::TYPE eInteractableItemType)
{
	auto item = GetAnInactiveInteractableItem();
	item->SetActive(true);
	item->SetSprite(CSpriteLoader::getInteractiveItemSprites(eInteractableItemType, m_arrayOfInteractableItemSizes[eInteractableItemType]), m_arrayOfInteractableItemSizes[eInteractableItemType]);
	item->setPosition(vec2Position);
	item->SetType(eInteractableItemType);
	item->SetTargetGO(m_pLayerGO);
}

void CGameObjectManager::AddInteractableItems(int numOfInteractableItems)
{
	int goListSize = m_pInteractableItemsList.size();
	for (int i = 0; i < numOfInteractableItems; i++)
	{
		auto item = CInteractableGameObject::create();
		DeactivateInteractableItem(item);
		item->setTag(goListSize + i);
		m_pInteractableItemsList.pushBack(item);
		this->addChild(item);
	}
}

CInteractableGameObject* CGameObjectManager::GetAnInactiveInteractableItem()
{
	// Find an inactive enemy
	for (int i = 0; i < m_pInteractableItemsList.size(); i++)
	{
		auto item = m_pInteractableItemsList.at(i);
		if (!item->GetActive())
		{
			item->resume();
			item->setVisible(true);
			return item;
		}
	}
	// Create more game objects if no empty game object
	AddInteractableItems(m_nAmountOfInteractableItemsToAdd);
	return GetAnInactiveInteractableItem();
}

void CGameObjectManager::DeactivateInteractableItem(CInteractableGameObject* item)
{
	item->SetActive(false);
	item->pause();
	item->setVisible(false);
}


void CGameObjectManager::SpawnPhysicsGO(cocos2d::Vec2 vec2Position, CPhysicsGameObject::TYPE PhysicsGOType)
{
	auto item = GetAnInactivePhysicsGO();
	item->SetActive(true);
	item->SetSprite(CSpriteLoader::getPhysicsGOSprites(PhysicsGOType, m_arrayOfPhysicsGOSizes[PhysicsGOType]), m_arrayOfPhysicsGOSizes[PhysicsGOType]);
	item->setPosition(vec2Position);
	item->SetType(PhysicsGOType);
	item->GeneratePhysicsBody();
}

void CGameObjectManager::AddPhysicsGO(int numOfPhysicsGO)
{
	int goListSize = m_pPhysicsGOList.size();
	for (int i = 0; i < numOfPhysicsGO; i++)
	{
		auto item = CPhysicsGameObject::create();
		DeactivatePhysicsGO(item);
		item->setTag(goListSize + i);
		m_pPhysicsGOList.pushBack(item);
		this->addChild(item);
	}
}

CPhysicsGameObject* CGameObjectManager::GetAnInactivePhysicsGO()
{
	// Find an inactive enemy
	for (int i = 0; i < m_pPhysicsGOList.size(); i++)
	{
		auto item = m_pPhysicsGOList.at(i);
		if (!item->GetActive())
		{
			item->resume();
			item->setVisible(true);
			return item;
		}
	}
	// Create more game objects if no empty game object
	AddPhysicsGO(m_nAmountOfPhysicsGOToAdd);
	return GetAnInactivePhysicsGO();
}

void CGameObjectManager::DeactivatePhysicsGO(CPhysicsGameObject* item)
{
	item->SetActive(false);
	item->pause();
	item->setVisible(false);
}
#include "GameObjectManager.h"
#include "Enemy.h"
#include "SpriteLoader.h"
#include "AnimationLoader.h"
#include "CollisionManager.h"

USING_NS_CC;

CGameObjectManager::CGameObjectManager(int numOfEnemies)
	: m_nAmountOfEnemiesToAdd(numOfEnemies)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// Set Size
	m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_WEAK]		= Size(visibleSize.width * 0.1f, visibleSize.height * 0.1f);
	m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_STRONG]	= Size(visibleSize.width * 0.11f, visibleSize.height * 0.125f);
	m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_POUNCER]	= Size(visibleSize.width * 0.11f, visibleSize.height * 0.11f);
	m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_SHOOTER]	= Size(visibleSize.width * 0.1f, visibleSize.height * 0.11f);
	m_arrayOfEnemySpriteSizes[CEnemy::ENEMY_TYPE_HYBRID]	= Size(visibleSize.width * 0.125f, visibleSize.height * 0.15f);
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
		CSpriteLoader::loadEnemiesSprites(m_arrayOfEnemySpriteSizes[i]);
		CAnimationLoader::loadEnemiesAnimates(m_arrayOfEnemySpriteSizes[i]);
	}
	CSpriteLoader::loadPlayerSprites();
	CAnimationLoader::loadPlayerAnimates();

	AddEnemies(numOfEnemies);
}


CGameObjectManager::~CGameObjectManager()
{
}


CGameObjectManager* CGameObjectManager::create(int numOfEnemies)
{
	CGameObjectManager * ret = new (std::nothrow) CGameObjectManager(numOfEnemies);
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
}

void CGameObjectManager::SpawnEnemy(Vec2 vec2Position, CEnemy::ENEMY_TYPE eEnemyType)
{
	auto enemy = GetAnInactiveEnemy();
	enemy->SetActive(true);
	enemy->SetSprite(CSpriteLoader::getEnemySprite(m_arrayOfEnemySpriteSizes[eEnemyType]), m_arrayOfEnemySpriteSizes[eEnemyType]);
	CCollisionManager::addPhysicBody(enemy);
	enemy->setPosition(vec2Position);
	enemy->Init(eEnemyType, m_pLayerGO, m_arrayOfEnemyMovementSpeed[eEnemyType], m_arrayOfEnemyAnimationSpeed[eEnemyType], m_arrayOfEnemyRanges[eEnemyType]);
	CAIEnemy* aiEnmey =	enemy->GetAI();;
	switch (eEnemyType)
	{
		case CEnemy::ENEMY_TYPE_POUNCER:
		{
			aiEnmey->SetPounceInfomations(0.5f, m_arrayOfEnemySpriteSizes[eEnemyType].height * 0.5f, 2.0f);
			break;
		}
		case CEnemy::ENEMY_TYPE_HYBRID:
		{
			aiEnmey->SetPounceInfomations(0.75f, m_arrayOfEnemySpriteSizes[eEnemyType].height * 0.5f, 2.0f);
			break;
		}
		default:
		{
			aiEnmey->SetPounceInfomations();
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
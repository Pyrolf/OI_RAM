#include "GameObjectManager.h"
#include "Enemy.h"
#include "SpriteLoader.h"

USING_NS_CC;

CGameObjectManager::CGameObjectManager(int numOfEnemies, Size enemySpriteSize)
	: m_nAmountOfEnemiesToAdd(numOfEnemies)
	, m_EnemySpriteSize(enemySpriteSize)
{
	AddEnemies(numOfEnemies);
}


CGameObjectManager::~CGameObjectManager()
{
}


CGameObjectManager* CGameObjectManager::create(int numOfEnemies, Size enemySpriteSize)
{
	CGameObjectManager * ret = new (std::nothrow) CGameObjectManager(numOfEnemies, enemySpriteSize);
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
		auto enmey = m_pEnemyList.at(i);
		if (enmey->GetActive())
		{
			enmey->Update(dt);
			if (enmey->GetAI()->GetCurrentState() == CAIEnemy::FSM_DIED)
			{
				DeactivateEnemy(enmey);
			}
		}
	}
}

void CGameObjectManager::SpawnEnemy(Vec2 vec2Position,
									CGameObject* pTargetGO, float fMovementSpeed, float fAnimationSpeed, float fDetectionRange, float fAttackRange )
{
	auto enemy = GetAnInactiveEnemy();
	enemy->SetActive(true);
	enemy->SetSprite(CSpriteLoader::getEnemySprite(m_EnemySpriteSize), m_EnemySpriteSize);
	enemy->AddPhysicsBodyBox();
	enemy->setPosition(vec2Position);
	enemy->Init(pTargetGO, fMovementSpeed, fAnimationSpeed, fDetectionRange, fAttackRange);
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
	enemy->RemovePhysicsBody();
	enemy->SetActive(false);
	enemy->pause();
	enemy->setVisible(false);
}
#include "GameObjectManager.h"
#include "Enemy.h"
#include "SpriteLoader.h"

USING_NS_CC;

CGameObjectManager::CGameObjectManager(int numOfEnemies)
	: m_nAmountOfEnemiesToAdd(numOfEnemies)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	m_EnemySpriteSize = Size(visibleSize.width * 0.1f, visibleSize.height * 0.1f);

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
		auto enmey = m_pEnemyList.at(i);
		if (enmey)
			enmey->Update(dt);
	}
}

void CGameObjectManager::SpawnEnemy(Vec2 vec2Position,
									CGameObject* pTargetGO, float speed, float fDetectionRange, float fAttackRange )
{
	auto enemy = GetAnInactiveEnemy();
	enemy->SetActive(true);
	enemy->SetSprite(CSpriteLoader::getEnemySprite(m_EnemySpriteSize), m_EnemySpriteSize);
	enemy->AddPhysicsBodyBox();
	enemy->setPosition(vec2Position);
	enemy->Init(pTargetGO, speed, fDetectionRange, fAttackRange);
}

void CGameObjectManager::AddEnemies(int numOfEnemies)
{
	int goListSize = m_pEnemyList.size();
	for (int i = 0; i < numOfEnemies; i++)
	{
		auto go = CEnemy::create();
		go->pause();
		go->setVisible(false);
		go->setTag(goListSize + i);
		m_pEnemyList.pushBack(go);
		this->addChild(go);
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
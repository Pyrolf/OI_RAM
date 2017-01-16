#include "InGameScene.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "SimpleAudioEngine.h"
#include "GUILayer.h"
#include "Enemy.h";
#include "InteractableGameObject.h"
#include "ParticleLoader.h"
#include "FileOperation.h"
#include "CollisionManager.h"
#include "FollowWithLerp.h"

USING_NS_CC;

CInGameScene::~CInGameScene()
{
	delete tileMapManager;

	removeAllChildrenWithCleanup(true);
}

Scene* CInGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setFixedUpdateRate(120);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -98 * 10));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
	auto layer = CInGameScene::create();
	layer->setName("CInGameScene");
    // add layer as a child to scene
    scene->addChild(layer);

	layer->m_pGUILayer = CGUILayer::addLayerToScene(scene);

    // return the scene
    return scene;
}

void CInGameScene::toInGameScene()
{
	Director* director = Director::getInstance();
	if (!director->getRunningScene())
		director->runWithScene(TransitionFade::create(1.0f, createScene(), Color3B(100, 100, 100)));
	else
		director->replaceScene(TransitionFade::create(1.0f, createScene(), Color3B(100, 100, 100)));
}

// on "init" you need to initialize your instance
bool CInGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	tileMapManager = new TilemapManager("tmx/Test_Level.tmx", this);

	initGameObjects();

	this->addChild(new CCollisionManager());

	m_nCoins = 0;
	m_nCoinsAddedToLabel = 0;

	m_nLives = 0;
	m_nLivesAddedToLabel = 0;

	m_nMana = 0;
	m_nManaMaxCap = 0;
	m_nManaAddedToBar = 0;

	// Last, get data
	getData();
	saveData();

    return true;
}

void CInGameScene::initGameObjects()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_pGOManager = CGameObjectManager::create();

	tileMapManager->SpawnGameObjects(m_pGOManager);

	////spawn player
	//m_pGOManager->SpawnPlayer(Vec2(	origin.x + visibleSize.width / 2,
	//								origin.y + visibleSize.height * 0.75f));
	////play particle at the player
	////CParticleLoader::createBleedingEffect(m_pGOManager->getPlayer());

	//// Spawn Enemy
	//// Weak
	//for (int i = 0; i < 1; i++)
	//{
	//	Vec2 position(	visibleSize.width * 0.15f + origin.x + visibleSize.width * 0.2f * i,
	//					visibleSize.height * 0.6f + origin.y);
	//	m_pGOManager->SpawnEnemy(position, CEnemy::ENEMY_TYPE_WEAK);
	//}
	//// Strong
	//for (int i = 0; i < 1; i++)
	//{
	//	Vec2 position(	visibleSize.width * 0.7f + origin.x + visibleSize.width * 0.2f * i,
	//					visibleSize.height * 0.6f + origin.y);
	//	m_pGOManager->SpawnEnemy(position, CEnemy::ENEMY_TYPE_STRONG);
	//}
	//// Pouncer
	//for (int i = 0; i < 1; i++)
	//{
	//	Vec2 position(	visibleSize.width * 1.0f + origin.x + visibleSize.width * 0.2f * i,
	//					visibleSize.height * 0.6f + origin.y);
	//	m_pGOManager->SpawnEnemy(position, CEnemy::ENEMY_TYPE_POUNCER);
	//}
	//// Shoot
	//for (int i = 0; i < 1; i++)
	//{
	//	Vec2 position(	visibleSize.width * 1.5f + origin.x + visibleSize.width * 0.2f * i,
	//					visibleSize.height * 0.6f + origin.y);
	//	m_pGOManager->SpawnEnemy(position, CEnemy::ENEMY_TYPE_SHOOTER);
	//}
	//// Hybrid
	//for (int i = 0; i < 1; i++)
	//{
	//	Vec2 position(	visibleSize.width * 2.0f + origin.x + visibleSize.width * 0.2f * i,
	//					visibleSize.height * 0.6f + origin.y);
	//	m_pGOManager->SpawnEnemy(position, CEnemy::ENEMY_TYPE_HYBRID);
	//}

	//// Spawn Items
	//for (int i = 0; i < 1; i++)
	//{
	//	Vec2 position(	visibleSize.width * 0.3f + origin.x + visibleSize.width * 0.2f * i,
	//					visibleSize.height * 0.6f + origin.y);
	//	m_pGOManager->SpawnPhysicsGO(position, CPhysicsGameObject::JUMPPAD);
	//}
	//for (int i = 0; i < 1; i++)
	//{
	//	Vec2 position(	visibleSize.width * 0.7f + origin.x + visibleSize.width * 0.2f * i,
	//					visibleSize.height * 0.6f + origin.y);
	//	m_pGOManager->SpawnInteractableItem(position, CInteractableGameObject::LIVE);
	//}
	//for (int i = 0; i < 1; i++)
	//{
	//	Vec2 position(	visibleSize.width * 1.0f + origin.x + visibleSize.width * 0.2f * i,
	//					visibleSize.height * 0.6f + origin.y);
	//	m_pGOManager->SpawnInteractableItem(position, CInteractableGameObject::MANA_POTION);
	//}

	auto pGOManagerNode = (Node*)m_pGOManager;
	pGOManagerNode->setTag(CHILD_TAG_GAMEOBJECT);
	this->addChild(pGOManagerNode, CHILD_TAG_GAMEOBJECT);
}

void CInGameScene::onEnterTransitionDidFinish()
{
	this->scheduleUpdate();
	if (m_pGUILayer)
		m_pGUILayer->ShowLayer(Vec2::ANCHOR_BOTTOM_LEFT);

	KeyboardManager::GetInstance()->removeFromParent();
	this->addChild(KeyboardManager::GetInstance());

	auto fll = FollowWithLerp::create(m_pGOManager->getPlayer(), 3, Rect(0, 0, tileMapManager->getTilemap()->getContentSize().width, tileMapManager->getTilemap()->getContentSize().height));

	this->runAction(fll);

	fll->setParallaxScrolling(tileMapManager->getTilemap());

}

void CInGameScene::update(float dt)
{
	m_pGOManager->getPlayer()->Update(dt);

	// AddCoins(1);
	if (m_nCoinsAddedToLabel != m_nCoins)
		AddCoinsToLabel();
	if (m_nLivesAddedToLabel != m_pGOManager->getPlayer()->GetLives())
		AddLivesToLabel();
	if (m_nManaAddedToBar != m_pGOManager->getPlayer()->getMana())
		AddManaToBar();
	if (m_pGOManager)
		m_pGOManager->Update(dt);

	Camera* c = Director::getInstance()->getRunningScene()->getDefaultCamera();

	m_pGUILayer->setPosition(c->getPosition() - m_pGUILayer->GetInitialCamPos());
}

void CInGameScene::endScene(bool bSave)
{
	this->unscheduleUpdate();
	if (bSave)
		saveData();
}

void CInGameScene::getData()
{
	std::vector<std::string> vec_sData = FileOperation::readFile(FileOperation::CURRENCY_DATA_FILE_TYPE);
	if (vec_sData.size() == 0)
		return;
	// Get data
	if (vec_sData.size() > 0)
		AddCoins(std::stoi(vec_sData[0]));
	/*if (vec_sData.size() > 1)
		AddLives(std::stoi(vec_sData[1]));
	else*/
		m_nLives = 3;
	/*if (vec_sData.size() > 2)
		AddMana(std::stoi(vec_sData[2]));
	else*/
		m_nMana = 25;
	/*if (vec_sData.size() > 3)
		m_nManaMaxCap = std::stoi(vec_sData[3]);
	else*/
		m_nManaMaxCap = 25;
}
void CInGameScene::saveData()
{
	// Save data
	std::stringstream ss;

	ss << m_nCoins << "\n";
	/*ss << m_nLives << "\n";
	ss << m_nMana << "\n";
	ss << m_nManaMaxCap << "\n";*/
	FileOperation::saveFile(ss.str(), FileOperation::CURRENCY_DATA_FILE_TYPE);
}

void CInGameScene::AddCoins(const unsigned int coins)
{
	m_nCoins += coins;
}

void CInGameScene::AddCoinsToLabel()
{
	if (m_pGUILayer)
	{
		m_nCoinsAddedToLabel = m_nCoins;
		m_pGUILayer->ChangeCoinsLabel(m_nCoinsAddedToLabel);
	}
}

void CInGameScene::AddLives(const unsigned int lives)
{
	m_pGOManager->getPlayer()->SetLives(m_pGOManager->getPlayer()->GetLives() + lives);
}

void CInGameScene::AddLivesToLabel()
{
	if (m_pGUILayer)
	{
		m_nLivesAddedToLabel = m_pGOManager->getPlayer()->GetLives();
		m_pGUILayer->ChangeLivesLabel(m_nLivesAddedToLabel);
	}
}

void CInGameScene::AddMana(const int mana)
{
	m_pGOManager->getPlayer()->setMana(m_pGOManager->getPlayer()->getMana() + mana);
}

void CInGameScene::AddManaToBar()
{
	if (m_pGUILayer)
	{
		m_nManaAddedToBar = m_pGOManager->getPlayer()->getMana();
		m_pGUILayer->ChangeManabar((float)m_nManaAddedToBar / (float)m_pGOManager->getPlayer()->getMaxMana() * 100.0f);
	}
}
#include "InGameScene.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "SimpleAudioEngine.h"
#include "GUILayer.h"
#include "Enemy.h";
#include "AnimationLoader.h"
#include "SpriteLoader.h"
#include "ParticleLoader.h"
#include "FileOperation.h"
#include "CollisionManager.h"

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
	scene->getPhysicsWorld()->setGravity(Vec2(0, -98 * 5));
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

	initGameObjects();

	KBM = new KeyboardManager();
	this->addChild(KBM);

	this->addChild(new CCollisionManager());

	tileMapManager = new TilemapManager("tmx/Test Level.tmx", this);

	player = new Player();
	player->setPosition(Vec2(	origin.x + visibleSize.width / 2,
								origin.y + visibleSize.height * 0.75f));
	this->addChild(player);

	CParticleLoader::createBleedingEffect(player);

	m_nPoints = 0;
	m_nPointsAddedToLabel = 0;

	// Last, get data
	getData();
	saveData();

    return true;
}

void CInGameScene::initGameObjects()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_pGOManager = CGameObjectManager::create(10);

	Size targetSize = m_pGOManager->GetEnemySpriteSize();
	// Load Sprites
	CSpriteLoader::loadEnemiesSprites(targetSize);
	// Load Animations
	CAnimationLoader::loadEnemiesAnimates(targetSize);

	// Spawn Enemy
	float speed = visibleSize.width * 0.01f;
	float detectionRange = visibleSize.width * 5.0f;
	float attackRange = visibleSize.width * 1.5f;
	for (int i = 0; i < 2; i++)
	{
		Vec2 position(	visibleSize.width * 0.2f + origin.x + visibleSize.width * 0.2f * i,
						visibleSize.height * 0.325f + origin.y);
		m_pGOManager->SpawnEnemy(	position,
									NULL, speed, detectionRange, attackRange);
	}

	auto pGOManagerNode = (Node*)m_pGOManager;
	pGOManagerNode->setTag(CHILD_TAG_GAMEOBJECT);
	this->addChild(pGOManagerNode, CHILD_TAG_GAMEOBJECT);
}

void CInGameScene::onEnterTransitionDidFinish()
{
	this->scheduleUpdate();
	if (m_pGUILayer)
		m_pGUILayer->ShowLayer(Vec2::ANCHOR_BOTTOM_LEFT);
}

bool upKeypress = false;

void CInGameScene::update(float dt)
{
	AddPoints(1);
	if (m_nPointsAddedToLabel != m_nPoints)
		AddPointsToLabel();
	if (m_pGOManager)
		m_pGOManager->Update(dt);

	Camera* c = Director::getInstance()->getRunningScene()->getDefaultCamera();
	if (KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_A))
	{
		player->Move(false, 1000, dt);
	}
	if (KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_D))
	{
		player->Move(true, 1000, dt);
	}
	if (KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) && !upKeypress)
	{
		upKeypress = true;
		player->Jump();
	}
	else if (!KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) && upKeypress)
	{
		upKeypress = false;
	}
	if (KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_S))
	{
		c->setPosition(c->getPositionX(), c->getPositionY() - dt * 500);
	}

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
	AddPoints(std::stoi(vec_sData[0]));
}
void CInGameScene::saveData()
{
	// Save data
	std::stringstream ss;

	ss << m_nPoints << "\n";
	FileOperation::saveFile(ss.str(), FileOperation::CURRENCY_DATA_FILE_TYPE);
}

void CInGameScene::AddPoints(const unsigned int points)
{
	m_nPoints += points;
}

void CInGameScene::AddPointsToLabel()
{
	if (m_pGUILayer)
	{
		m_nPointsAddedToLabel = m_nPoints;
		m_pGUILayer->ChangePointsLabel(m_nPointsAddedToLabel);
	}
}
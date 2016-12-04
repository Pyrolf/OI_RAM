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

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
    auto layer = CInGameScene::create();

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

	this->scheduleUpdate();

	initGameObjects();

	KBM = new KeyboardManager();
	this->addChild(KBM);

	tileMapManager = new TilemapManager("tmx/Test Level.tmx", this);

	player = new Player();
	player->setPosition(Vec2(	origin.x + visibleSize.width / 2,
								origin.y + visibleSize.height * 0.75f));
	this->addChild(player);

	CParticleLoader::createBleedingEffect(player);

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

void CInGameScene::update(float dt)
{
	if (m_pGOManager)
		m_pGOManager->Update(dt);

	Camera* c = Director::getInstance()->getRunningScene()->getDefaultCamera();
	if (KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_A))
	{
		c->setPosition(c->getPositionX() - dt * 500, c->getPositionY());
	}
	if (KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_D))
	{
		c->setPosition(c->getPositionX() + dt * 500, c->getPositionY());
	}
	if (KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_W))
	{
		c->setPosition(c->getPositionX(), c->getPositionY() + dt * 500);
	}
	if (KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || KBM->isKeyPressed(EventKeyboard::KeyCode::KEY_S))
	{
		c->setPosition(c->getPositionX(), c->getPositionY() - dt * 500);
	}

	m_pGUILayer->setPosition(c->getPosition() - m_pGUILayer->GetInitialCamPos());
}

void CInGameScene::getData()
{
	std::vector<std::string> Data2 = FileOperation::readFile();
	if (Data2.size() == 0)
		return;
	// Write data
	int one = std::stoi(Data2[0]);
	int two = std::stoi(Data2[1]);
	int three = std::stoi(Data2[2]);
}
void CInGameScene::saveData()
{
	// Save data
	std::string Data1("");
	Data1 += "1\n";
	Data1 += "2\n";
	Data1 += "3\n";
	FileOperation::saveFile(Data1);
}
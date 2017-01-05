#include "InGameScene.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "SimpleAudioEngine.h"
#include "GUILayer.h"
#include "Enemy.h";
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

	initGameObjects();

	this->addChild(new CCollisionManager());

	tileMapManager = new TilemapManager("tmx/Test_Level.tmx", this);

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

	//spawn player
	m_pGOManager->SpawnPlayer(Vec2(	origin.x + visibleSize.width / 2,
									origin.y + visibleSize.height * 0.75f));
	//play particle at the player
	//CParticleLoader::createBleedingEffect(m_pGOManager->getPlayer());

	// Spawn Enemy
	for (int i = 0; i < 1; i++)
	{
		Vec2 position(	visibleSize.width * 0.2f + origin.x + visibleSize.width * 0.2f * i,
						visibleSize.height * 0.6f + origin.y);
		m_pGOManager->SpawnEnemy(position, CEnemy::ENEMY_TYPE_POUNCER);
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

	KeyboardManager::GetInstance()->removeFromParent();
	this->addChild(KeyboardManager::GetInstance());

	auto fll = FollowWithLerp::create(m_pGOManager->getPlayer(), 3, Rect(0, 0, tileMapManager->getTilemap()->getContentSize().width, tileMapManager->getTilemap()->getContentSize().height));

	this->runAction(fll);

	fll->setParallaxScrolling(tileMapManager->getTilemap());

	//tileMapManager->setLightEffect(_effect);

	/*auto avds = CSpriteLoader::getEnemySprite(Size(64, 64));
	this->addChild(avds);
	avds->setPosition(64, 64);
	avds->setAnchorPoint(Vec2(0, 0));

	RenderTexture* r = RenderTexture::create(700, 700);
	
	r->beginWithClear(1, 1, 1, 0);
	m_pGOManager->getPlayer()->GetSprite()->visit();
	avds->visit();
	r->end();

	auto assd = Sprite::createWithTexture(r->getSprite()->getTexture());
	assd->setAnchorPoint(Vec2(0, 0));
	addChild(assd);

	RenderTexture* ra = RenderTexture::create(700, 700);
	ra->beginWithClear(1, 1, 1, 0);
	assd->visit();
	ra->end();

	auto assds = Sprite::createWithTexture(ra->getSprite()->getTexture());
	assds->getTexture()->retain();
	assds->setAnchorPoint(Vec2(0, 0));
	addChild(assds);

	assd->removeFromParent();
	
	avds->removeFromParent();*/
	//CC_SAFE_DELETE(assd);
	//bool a = e.updateWithData(tileMapManager->, 0, 0, 40, 40);
	//m_pGOManager->getPlayer()->GetSprite()->setTexture(r->getSprite()->getTexture());
}

void CInGameScene::update(float dt)
{
	
	m_pGOManager->getPlayer()->update(dt);

	AddPoints(1);
	if (m_nPointsAddedToLabel != m_nPoints)
		AddPointsToLabel();
	if (m_pGOManager)
		m_pGOManager->Update(dt);

	Camera* c = Director::getInstance()->getRunningScene()->getDefaultCamera();

	/*if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_A))
	{
		c->setPosition(c->getPosition() - Vec2(100, 0));
	}
	if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_D))
	{
		c->setPosition(c->getPosition() + Vec2(100, 00));
	}
	if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW))
	{
		c->setPosition(c->getPosition() + Vec2(0, 100));
	}
	if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW))
	{
		c->setPosition(c->getPosition() - Vec2(0, 100));
	}*/

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
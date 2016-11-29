#include "InGameScene.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "SimpleAudioEngine.h"
#include "GUILayer.h"

USING_NS_CC;

CInGameScene::~CInGameScene()
{
	delete tileMapManager;
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

	// Monster sprite
	Size targetSize(visibleSize.width * 0.15f, visibleSize.height * 0.2f);
	auto sprite = Sprite::create("animations/monsters/monster1/idle/frame_1.png");
	sprite->setScale(targetSize.width / sprite->getContentSize().width, targetSize.height / sprite->getContentSize().height);
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	// Load sprites
	CAnimationSystem::getInstance()->loadAnimation("animations/monsters/monster1/idle/frame_%d.png", targetSize, 8);
	CAnimationSystem::getInstance()->loadAnimation("animations/monsters/monster1/walking/frame_%d.png", targetSize, 8);
	
	// Start
	Sprite* monster = CSpriteSystem::getInstance()->createSprite("animations/monsters/monster1/idle/frame_1.png", targetSize);
	Vec2 leftPos(	origin.x + monster->getScaleX() *  monster->getContentSize().width * 0.5f,
					visibleSize.height * 0.5f + origin.y);
	Vec2 rightPos(	visibleSize.width + origin.x - monster->getScaleX() *  monster->getContentSize().width * 0.5f,
					visibleSize.height * 0.5f + origin.y);
	monster->setPosition(leftPos);
	float movingDuration = 3.0f;
	auto idlingAnimateAction = CallFunc::create([this]()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Size targetSize(visibleSize.width * 0.15f, visibleSize.height * 0.2f);
		auto action = RepeatForever::create((CAnimationSystem::getInstance()->getAnimate("animations/monsters/monster1/idle/frame_%d.png", targetSize, 8, 0.05f)));
		action->setTag(100);
		auto monster = this->getChildByTag(100);
		monster->stopActionByTag(100);
		monster->runAction(action);
	});
	auto idlingTimeAction = DelayTime::create(1.0f);
	auto walkingAnimateAction = CallFunc::create([this]()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Size targetSize(visibleSize.width * 0.15f, visibleSize.height * 0.2f);
		auto action = RepeatForever::create(CAnimationSystem::getInstance()->getAnimate("animations/monsters/monster1/walking/frame_%d.png", targetSize, 8, 0.125f));
		action->setTag(100);
		auto monster = (Sprite*)this->getChildByTag(100);
		monster->stopActionByTag(100);
		monster->runAction(action);
		monster->setFlippedX(!monster->isFlippedX());
	});
	auto moveToRightAction = MoveTo::create(movingDuration, rightPos);
	auto moveToLeftAction = MoveTo::create(movingDuration, leftPos);
	auto action = RepeatForever::create(Sequence::create(	idlingAnimateAction, idlingTimeAction,
															walkingAnimateAction, moveToRightAction,
															idlingAnimateAction, idlingTimeAction,
															walkingAnimateAction, moveToLeftAction,
															NULL));
	monster->runAction(action);
	monster->setTag(100);
	this->addChild(monster, 1);
    

	KBM = new KeyboardManager();
	this->addChild(KBM);

	tileMapManager = new TilemapManager("tmx/Test Level.tmx", this);

	player = new Player();
	player->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height));
	this->addChild(player);

    return true;
}

void CInGameScene::update(float dt)
{
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
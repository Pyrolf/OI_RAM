#include "InGameScene.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "SimpleAudioEngine.h"
#include "PauseLayer.h"

USING_NS_CC;


Scene* CInGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CInGameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

	layer->m_pPauseLayer = CPauseLayer::addLayerToScene(scene);

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
	
	initPause();

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
    
    return true;
}

void CInGameScene::initPause()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// Pause Button
	auto pauseButton = MenuItemImage::create(	"CloseNormal.png",
												"CloseSelected.png",
												CC_CALLBACK_1(CInGameScene::pauseCallback, this));
	pauseButton->setPosition(Vec2(	origin.x + visibleSize.width - pauseButton->getContentSize().width * 0.5f,
									origin.y + pauseButton->getContentSize().height * 0.5f));
	// create pause menu, it's an autorelease object
	auto pauseMenu = Menu::create(pauseButton, NULL);
	pauseMenu->setPosition(origin);
	this->addChild(pauseMenu, 1);
}

void CInGameScene::update(float dt)
{
}


void CInGameScene::pauseCallback(Ref* pSender)
{
	Director::getInstance()->pause();
	m_pPauseLayer->ShowLayer();
}
#include "HelloWorldScene.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::toHelloWorldScene()
{
	if (!Director::getInstance()->getRunningScene())
		Director::getInstance()->runWithScene(TransitionFade::create(1.0f, createScene(), Color3B(100, 100, 100)));
	else
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, createScene(), Color3B(100, 100, 100)));
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(origin);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("animations/knight/idle/frame_1.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);


	// Load sprites
	Size targetSize(visibleSize.width * 0.15f, visibleSize.height * 0.2f);
	CAnimationSystem::getInstance()->loadAnimation("animations/monsters/monster1/idle/frame_%d.png", targetSize, 8);
	CAnimationSystem::getInstance()->loadAnimation("animations/monsters/monster1/walking/frame_%d.png", targetSize, 8);
	
	// Start
	Sprite* monster = CSpriteSystem::getInstance()->createSprite("animations/monsters/monster1/walking/frame_1.png", targetSize);
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

void HelloWorld::update(float dt)
{
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	// 'layer' is an autorelease object
	auto layer2 = CMainMenuScene::create();

	// add layer as a child to scene
	Director::getInstance()->getRunningScene()->addChild(layer2);

   // Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
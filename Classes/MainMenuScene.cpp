#include "MainMenuScene.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* CMainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CMainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void CMainMenuScene::toMainMenuScene()
{
	Director* director = Director::getInstance();
	if (!director->getRunningScene())
		director->runWithScene(TransitionFade::create(1.0f, createScene(), Color3B(100, 100, 100)));
	else
		director->replaceScene(TransitionFade::create(1.0f, createScene(), Color3B(100, 100, 100)));
}

// on "init" you need to initialize your instance
bool CMainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// Create background
	auto background = CSpriteSystem::getInstance()->createSprite("HelloWorld.png", visibleSize);
	background->setPosition(origin + visibleSize * 0.5f);
	this->addChild(background, CHILD_TAG_BACKGROUND);

	// Create menu itmes
	Vector<MenuItem*> menuItemList;
	// Create Title
	// Use label for now, may change to sprite image
	auto titleLabel = MenuItemLabel::create(Label::createWithTTF("OI-RAM!", "fonts/Marker Felt.ttf", visibleSize.height * 0.25f));
	titleLabel->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.75f));
	titleLabel->setColor(Color3B::MAGENTA);
	menuItemList.pushBack(titleLabel);

	// Create buttons
	Size buttonSize(visibleSize.width * 0.25f,
					visibleSize.height * 0.1f);
	Vec2 buttonPositionOffset(0, -visibleSize.height * 0.11f);
	Color3B buttonColor(Color3B::YELLOW);
	// Create start button
	auto startButton = MenuItemImage::create(	"CloseNormal.png",
												"CloseSelected.png",
												CC_CALLBACK_1(CMainMenuScene::startGameCallback, this));
	startButton->setScale(	buttonSize.width * 1.5f / startButton->getContentSize().width,
							buttonSize.height * 1.5f / startButton->getContentSize().height);
	startButton->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.5f));
	startButton->setColor(buttonColor);
	menuItemList.pushBack(startButton);
	
	// Create store button
	auto storeButton = MenuItemImage::create(	"CloseNormal.png",
												"CloseSelected.png",
												CC_CALLBACK_1(CMainMenuScene::goStoreCallback, this));
	storeButton->setScale(	buttonSize.width / storeButton->getContentSize().width,
							buttonSize.height / storeButton->getContentSize().height);
	storeButton->setPosition(startButton->getPosition() - Vec2(0, (startButton->getScaleY() * startButton->getContentSize().height) * 0.5f) + buttonPositionOffset);
	storeButton->setColor(buttonColor);
	menuItemList.pushBack(storeButton);
	
	// Create exit button
	auto exitButton = MenuItemImage::create("CloseNormal.png",
											"CloseSelected.png",
											CC_CALLBACK_1(CMainMenuScene::exitGameCallback, this));
	exitButton->setScale(	buttonSize.width / exitButton->getContentSize().width,
							buttonSize.height / exitButton->getContentSize().height);
	exitButton->setPosition(storeButton->getPosition() - Vec2(0, (storeButton->getScaleY() * storeButton->getContentSize().height) * 0.5f) + buttonPositionOffset);
	exitButton->setColor(buttonColor);
	menuItemList.pushBack(exitButton);

    // Create menu
	auto menu = Menu::createWithArray(menuItemList);
    menu->setPosition(origin);
	this->addChild(menu, CHILD_TAG_MENU);

    return true;
}

void CMainMenuScene::startGameCallback(Ref* pSender)
{
	CGameStateManager::getInstance()->switchState(CGameStateManager::STATE_GAMEPLAY);
}
void CMainMenuScene::goStoreCallback(Ref* pSender)
{
	CGameStateManager::getInstance()->switchState(CGameStateManager::STATE_STORE);
}
void CMainMenuScene::exitGameCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
#include "StoreScene.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* CStoreScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CStoreScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void CStoreScene::toStoreScene()
{
	Director* director = Director::getInstance();
	if (!director->getRunningScene())
		director->runWithScene(TransitionFade::create(1.0f, createScene(), Color3B(100, 100, 100)));
	else
		director->replaceScene(TransitionFade::create(1.0f, createScene(), Color3B(100, 100, 100)));
}

// on "init" you need to initialize your instance
bool CStoreScene::init()
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
	auto background = CSpriteSystem::getInstance()->getSprite("HelloWorld.png", visibleSize);
	background->setPosition(origin + visibleSize * 0.5f);
	this->addChild(background, CHILD_TAG_BACKGROUND);

	// Create menu itmes
	Vector<MenuItem*> menuItemList;
	// Create Title
	// Use label for now, may change to sprite image
	auto titleLabel = MenuItemLabel::create(Label::createWithTTF("STORE", "fonts/Marker Felt.ttf", visibleSize.height * 0.15f));
	titleLabel->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.9f));
	titleLabel->setColor(Color3B::MAGENTA);
	menuItemList.pushBack(titleLabel);

	// Create back to main menu button
	auto backToMainMenuButton = MenuItemImage::create(	"CloseNormal.png",
														"CloseSelected.png",
														CC_CALLBACK_1(CStoreScene::backToMainMenuCallback, this));
	backToMainMenuButton->setScale(	visibleSize.height * 0.15f / backToMainMenuButton->getContentSize().width,
									visibleSize.height * 0.15f / backToMainMenuButton->getContentSize().height);
	backToMainMenuButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	float offSet = visibleSize.height * 0.025f;
	backToMainMenuButton->setPosition(origin + Vec2(offSet, offSet));
	menuItemList.pushBack(backToMainMenuButton);

    // Create menu
	auto menu = Menu::createWithArray(menuItemList);
    menu->setPosition(origin);
	this->addChild(menu, CHILD_TAG_MENU);

    return true;
}

void CStoreScene::backToMainMenuCallback(Ref* pSender)
{
	CGameStateManager::getInstance()->switchState(CGameStateManager::STATE_MAINMENU);
}
#include "MainMenuScene.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "SimpleAudioEngine.h"
#include "FileOperation.h"

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
	auto background = CSpriteSystem::getInstance()->getSprite("HelloWorld.png", visibleSize);
	background->setPosition(origin + visibleSize * 0.5f);
	this->addChild(background, CHILD_TAG_BACKGROUND);

	// Label
	std::string font = "fonts/Marker Felt.ttf";
	float fontSize = visibleSize.height * 0.05f;
	Color3B labelColor(Color3B::MAGENTA);

	// Create menu itmes
	Vector<MenuItem*> menuItemList;
	// Create Title
	// Use label for now, may change to sprite image
	auto titleLabel = Label::createWithTTF("OI-RAM!", font, visibleSize.height * 0.25f);
	titleLabel->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.8f));
	titleLabel->setColor(labelColor);
	this->addChild(titleLabel);

	// Create buttons
	/*Size buttonSize(visibleSize.width * 0.25f,
					visibleSize.height * 0.1f);*/
	Vec2 buttonPositionOffset(0, -visibleSize.height * 0.15f);
	// Create start button
	auto startButton = MenuItemImage::create(	"images/ui/button.png",
												"images/ui/button_selected.png",
												CC_CALLBACK_1(CMainMenuScene::startGameCallback, this));
	/*startButton->setScale(	buttonSize.width * 1.5f / startButton->getContentSize().width,
							buttonSize.height * 1.5f / startButton->getContentSize().height);*/
	startButton->setScale(1.5f);
	startButton->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.55f));
	menuItemList.pushBack(startButton);
	// start label
	auto startLabel = MenuItemLabel::create(Label::createWithTTF("Start", font, fontSize));
	startLabel->setPosition(Vec2(	startButton->getContentSize().width * 0.5f,
									startButton->getContentSize().height * 0.5f));
	startLabel->setColor(labelColor);
	startButton->addChild(startLabel);
	
	//// Create store button
	//auto storeButton = MenuItemImage::create(	"images/ui/button.png",
	//											"images/ui/button_selected.png",
	//											CC_CALLBACK_1(CMainMenuScene::goStoreCallback, this));
	///*storeButton->setScale(	buttonSize.width / storeButton->getContentSize().width,
	//						buttonSize.height / storeButton->getContentSize().height);*/
	//storeButton->setPosition(startButton->getPosition() - Vec2(0, (startButton->getScaleY() * startButton->getContentSize().height) * 0.5f) + buttonPositionOffset);
	//menuItemList.pushBack(storeButton);
	//// store label
	//auto storeLabel = MenuItemLabel::create(Label::createWithTTF("Store", font, fontSize));
	//storeLabel->setPosition(Vec2(	storeButton->getContentSize().width * 0.5f,
	//								storeButton->getContentSize().height * 0.5f));
	//storeLabel->setColor(labelColor);
	//storeButton->addChild(storeLabel);
	
	// Create exit button
	auto exitButton = MenuItemImage::create(	"images/ui/button.png",
												"images/ui/button_selected.png",
											CC_CALLBACK_1(CMainMenuScene::exitGameCallback, this));
	/*exitButton->setScale(	buttonSize.width / exitButton->getContentSize().width,
							buttonSize.height / exitButton->getContentSize().height);*/
	exitButton->setPosition(startButton->getPosition() - Vec2(0, (startButton->getContentSize().height) * 0.5f) + buttonPositionOffset);
	menuItemList.pushBack(exitButton);
	// exit label
	auto exitLabel = MenuItemLabel::create(Label::createWithTTF("Exit", font, fontSize));
	exitLabel->setPosition(Vec2(exitButton->getContentSize().width * 0.5f,
								exitButton->getContentSize().height * 0.5f));
	exitLabel->setColor(labelColor);
	exitButton->addChild(exitLabel);

    // Create menu
	auto menu = Menu::createWithArray(menuItemList);
	menu->setPosition(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(menu, CHILD_TAG_MENU);

    return true;
}

void CMainMenuScene::startGameCallback(Ref* pSender)
{
	// Save data
	std::stringstream ss1, ss2, ss3;

	ss1 << 0 << "\n";
	FileOperation::saveFile(ss1.str(), FileOperation::CURRENCY_DATA_FILE_TYPE);

	ss2 << 3 << "\n";
	ss2 << 25 << "\n";
	FileOperation::saveFile(ss2.str(), FileOperation::PLAYER_DATA_FILE_TYPE);

	ss3 << 1 << "\n";
	FileOperation::saveFile(ss3.str(), FileOperation::LEVEL_DATA_FILE_TYPE);

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
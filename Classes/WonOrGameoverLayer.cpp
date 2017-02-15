#include "WonOrGameoverLayer.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "InGameScene.h"
#include "SoundLoader.h"

USING_NS_CC;

CWonOrGameoverLayer* CWonOrGameoverLayer::addLayerToScene(Scene* scene)
{
    // 'layer' is an autorelease object
    auto layer = CWonOrGameoverLayer::create();
	layer->setName("CWonOrGameoverLayer");
    // add layer as a child to scene
    scene->addChild(layer);

	return layer;
}

// on "init" you need to initialize your instance
bool CWonOrGameoverLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Create menu itmes
	Vector<MenuItem*> menuItemList;
	
	auto background = MenuItemImage::create(	"images/ui/bloody_hand.png",
												"images/ui/bloody_hand.png");
	background->setScale(	visibleSize.width * 1.0f / background->getContentSize().width,
							visibleSize.height * 1.0f / background->getContentSize().height);
	background->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.5f));
	menuItemList.pushBack(background);

	// Label
	std::string font = "fonts/Marker Felt.ttf";
	float fontSize = visibleSize.height * 0.05f;
	Color3B labelColor(Color3B::MAGENTA);

	// Create Title
	// Use label for now, may change to sprite image
	auto wonLabel = Label::createWithTTF("WON", font, visibleSize.height * 0.25f);
	wonLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.75f));
	wonLabel->setColor(labelColor);
	wonLabel->setTag(CHILD_TAG_WON_LABEL);
	this->addChild(wonLabel, 1);
	
	auto gameoverLabel = Label::createWithTTF("GAMEOVER", font, visibleSize.height * 0.25f);
	gameoverLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.75f));
	gameoverLabel->setColor(labelColor);
	gameoverLabel->setTag(CHILD_TAG_GAMEOVER_LABEL);
	this->addChild(gameoverLabel, 1);

	// Create buttons
	/*Size buttonSize(visibleSize.width * 0.25f,
					visibleSize.height * 0.1f);*/
	Vec2 buttonPositionOffset(0, -visibleSize.height * 0.11f);
	// Create next level button
	auto nextLevelButton = MenuItemImage::create(	"images/ui/button.png",
												"images/ui/button_selected.png",
												CC_CALLBACK_1(CWonOrGameoverLayer::nextLevelCallback, this));
	/*nextLevelButton->setScale(	buttonSize.width * 1.5f / resumeButton->getContentSize().width,
									buttonSize.height * 1.5f / resumeButton->getContentSize().height);*/
	nextLevelButton->setPosition(Vec2(origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.5f));
	nextLevelButton->setTag(CHILD_TAG_NEXT_LEVEL_BUTTON);
	menuItemList.pushBack(nextLevelButton);
	// next level label
	auto nextLevelLabel = MenuItemLabel::create(Label::createWithTTF("Next Level", font, fontSize));
	nextLevelLabel->setPosition(Vec2(nextLevelButton->getContentSize().width * 0.5f,
									nextLevelButton->getContentSize().height * 0.5f));
	nextLevelLabel->setColor(labelColor);
	nextLevelButton->addChild(nextLevelLabel);
	
	// Create restart button
	auto restartButton = MenuItemImage::create(	"images/ui/button.png",
												"images/ui/button_selected.png",
												CC_CALLBACK_1(CWonOrGameoverLayer::restartCallback, this));
	/*restartButton->setScale(	buttonSize.width / restartButton->getContentSize().width,
								buttonSize.height / restartButton->getContentSize().height);*/
	restartButton->setScale(0.75f);
	restartButton->setPosition(nextLevelButton->getPosition() - Vec2(0, (nextLevelButton->getScaleY() * nextLevelButton->getContentSize().height) * 0.5f) + buttonPositionOffset);
	menuItemList.pushBack(restartButton);
	// restart label
	auto restartLabel = MenuItemLabel::create(Label::createWithTTF("Restart", font, fontSize));
	restartLabel->setPosition(Vec2(	restartButton->getContentSize().width * 0.5f,
									restartButton->getContentSize().height * 0.5f));
	restartLabel->setColor(labelColor);
	restartButton->addChild(restartLabel);
	
	// Create quit button
	auto quitButton = MenuItemImage::create(	"images/ui/button.png",
												"images/ui/button_selected.png",
											CC_CALLBACK_1(CWonOrGameoverLayer::quitCallback, this));
	//quitButton->setScale(	buttonSize.width / quitButton->getContentSize().width,
	//						buttonSize.height / quitButton->getContentSize().height);
	quitButton->setScale(0.75f);
	quitButton->setPosition(restartButton->getPosition() - Vec2(0, restartButton->getScaleY() * restartButton->getContentSize().height * 0.5f) + buttonPositionOffset);
	menuItemList.pushBack(quitButton);
	// quit label
	auto quitLabel = MenuItemLabel::create(Label::createWithTTF("Quit", font, fontSize));
	quitLabel->setPosition(Vec2(quitButton->getContentSize().width * 0.5f,
								quitButton->getContentSize().height * 0.5f));
	quitLabel->setColor(labelColor);
	quitButton->addChild(quitLabel);

    // Create menu
	auto menu = Menu::createWithArray(menuItemList);
	menu->setPosition(Vec2::ANCHOR_BOTTOM_LEFT);
	menu->setTag(CHILD_TAG_MENU);
	this->addChild(menu);



	// Hide Pause Layer
	HideLayer();

	return true;
}

void CWonOrGameoverLayer::HideLayer()
{
	setVisible(false);
}
void CWonOrGameoverLayer::ShowLayer(Vec2 offset, bool showWin)
{
	Director::getInstance()->pause();
	if (Director::getInstance()->getRunningScene()->getPhysicsWorld())
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);

	this->setPosition(offset);
	setVisible(true);

	// Show Won / Gameover layer
	auto wonLabel = (Label*)this->getChildByTag(CHILD_TAG_WON_LABEL);
	wonLabel->setVisible(showWin);

	auto gameoverLabel = (Label*)this->getChildByTag(CHILD_TAG_GAMEOVER_LABEL);
	gameoverLabel->setVisible(!showWin);

	auto menu = (Menu*)this->getChildByTag(CHILD_TAG_MENU);
	auto nextLevelButton = (MenuItemImage*)menu->getChildByTag(CHILD_TAG_NEXT_LEVEL_BUTTON);

	Scene* scene = Director::getInstance()->getRunningScene();
	auto gameScene = (CInGameScene*)scene->getChildByName("CInGameScene");
	if (!gameScene->IfLastLevel())
	{
		nextLevelButton->setVisible(showWin);
	}
	else
	{
		nextLevelButton->setVisible(false);
	}
	CSoundLoader::stopBackgroundMusic();
	if (!showWin)
	{
		CSoundLoader::playSoundEffect(CSoundLoader::PAIN_SOUND_EFFECT);
	}
	else
	{
		CSoundLoader::playSoundEffect(CSoundLoader::APPLAUSE_SOUND_EFFECT);
	}
}

void CWonOrGameoverLayer::nextLevelCallback(Ref* pSender)
{
	CSoundLoader::playSoundEffect(CSoundLoader::SELECT_SOUND_EFFECT);
	Director::getInstance()->resume();
	Scene* scene = Director::getInstance()->getRunningScene();
	if (scene->getPhysicsWorld())
		scene->getPhysicsWorld()->setSpeed(1);
	// End Scene
	auto gameScene = (CInGameScene*)scene->getChildByName("CInGameScene");
	if (gameScene)
	{
		gameScene->NextLevel();
		// Save data
		gameScene->endScene(true);
	}
	CGameStateManager::getInstance()->switchState(CGameStateManager::STATE_STORE);
}
void CWonOrGameoverLayer::restartCallback(Ref* pSender)
{
	CSoundLoader::playSoundEffect(CSoundLoader::SELECT_SOUND_EFFECT);
	Director::getInstance()->resume();
	Scene* scene = Director::getInstance()->getRunningScene();
	if (scene->getPhysicsWorld())
		scene->getPhysicsWorld()->setSpeed(1);
	// End Scene
	auto gameScene = (CInGameScene*)scene->getChildByName("CInGameScene");
	if (gameScene)
	{
		// Save data
		gameScene->endScene(true);
	}
	CGameStateManager::getInstance()->switchState(CGameStateManager::STATE_GAMEPLAY);
}
void CWonOrGameoverLayer::quitCallback(Ref* pSender)
{
	CSoundLoader::playSoundEffect(CSoundLoader::SELECT_SOUND_EFFECT);
	Director::getInstance()->resume();
	Scene* scene = Director::getInstance()->getRunningScene();
	if (scene->getPhysicsWorld())
		scene->getPhysicsWorld()->setSpeed(1);
	// End Scene
	auto gameScene = (CInGameScene*)scene->getChildByName("CInGameScene");
	if (gameScene)
	{
		// Save data
		gameScene->endScene(true);
	}
	CGameStateManager::getInstance()->switchState(CGameStateManager::STATE_MAINMENU);
}
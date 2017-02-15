#include "PauseLayer.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "InGameScene.h"
#include "SoundLoader.h"

USING_NS_CC;

CPauseLayer* CPauseLayer::addLayerToScene(Scene* scene)
{
    // 'layer' is an autorelease object
    auto layer = CPauseLayer::create();
	layer->setName("CPauseLayer");
    // add layer as a child to scene
    scene->addChild(layer);

	return layer;
}

// on "init" you need to initialize your instance
bool CPauseLayer::init()
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
	
	auto background = MenuItemImage::create("images/ui/boom.png",
											"images/ui/boom.png");
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
	auto titleLabel = Label::createWithTTF("Pause", font, visibleSize.height * 0.2f);
	titleLabel->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.7f));
	titleLabel->setColor(labelColor);
	this->addChild(titleLabel, 1);

	// Create buttons
	/*Size buttonSize(visibleSize.width * 0.25f,
					visibleSize.height * 0.1f);*/
	Vec2 buttonPositionOffset(0, -visibleSize.height * 0.07f);
	// Create resume button
	auto resumeButton = MenuItemImage::create(	"images/ui/button.png",
												"images/ui/button_selected.png",
												CC_CALLBACK_1(CPauseLayer::resumeCallback, this));
	/*resumeButton->setScale(	buttonSize.width * 1.5f / resumeButton->getContentSize().width,
							buttonSize.height * 1.5f / resumeButton->getContentSize().height);*/
	resumeButton->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.5f));
	menuItemList.pushBack(resumeButton);
	// resume label
	auto resumeLabel = MenuItemLabel::create(Label::createWithTTF("Resume", font, fontSize));
	resumeLabel->setPosition(Vec2(	resumeButton->getContentSize().width * 0.5f,
									resumeButton->getContentSize().height * 0.5f));
	resumeLabel->setColor(labelColor);
	resumeButton->addChild(resumeLabel);
	
	// Create restart button
	auto restartButton = MenuItemImage::create(	"images/ui/button.png",
												"images/ui/button_selected.png",
												CC_CALLBACK_1(CPauseLayer::restartCallback, this));
	/*restartButton->setScale(	buttonSize.width / restartButton->getContentSize().width,
								buttonSize.height / restartButton->getContentSize().height);*/
	restartButton->setScale(0.75f);
	restartButton->setPosition(resumeButton->getPosition() - Vec2(0, (resumeButton->getScaleY() * resumeButton->getContentSize().height) * 0.5f) + buttonPositionOffset);
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
											CC_CALLBACK_1(CPauseLayer::quitCallback, this));
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
	this->addChild(menu);



	// Hide Pause Layer
	HideLayer();

	return true;
}

void CPauseLayer::HideLayer()
{
	setVisible(false);
}
void CPauseLayer::ShowLayer(Vec2 offset)
{
	this->setPosition(offset);
	setVisible(true);
}

void CPauseLayer::resumeCallback(Ref* pSender)
{
	CSoundLoader::pauseSounds(false);
	CSoundLoader::playSoundEffect(CSoundLoader::SELECT_SOUND_EFFECT);
	Director::getInstance()->resume();
	Scene* scene = Director::getInstance()->getRunningScene();
	if (scene->getPhysicsWorld())
		scene->getPhysicsWorld()->setSpeed(1);
	HideLayer();
}
void CPauseLayer::restartCallback(Ref* pSender)
{
	CSoundLoader::pauseSounds(false);
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
void CPauseLayer::quitCallback(Ref* pSender)
{
	CSoundLoader::pauseSounds(false);
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
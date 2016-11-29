#include "PauseLayer.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"

USING_NS_CC;

CPauseLayer* CPauseLayer::addLayerToScene(Scene* scene)
{
    // 'layer' is an autorelease object
    auto layer = CPauseLayer::create();

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

	
	// Create background
	auto background = CSpriteSystem::getInstance()->createSprite("HelloWorld.png", Size(visibleSize.width * 0.6f, visibleSize.height * 0.95f));
	background->setPosition(origin + visibleSize * 0.5f);
	background->setTag(CHILD_TAG_BACKGROUND);
	this->addChild(background, CHILD_TAG_BACKGROUND);

	// Create menu itmes
	Vector<MenuItem*> menuItemList;
	// Create Title
	// Use label for now, may change to sprite image
	auto titleLabel = MenuItemLabel::create(Label::createWithTTF("Pause", "fonts/Marker Felt.ttf", visibleSize.height * 0.25f));
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
	auto resumeButton = MenuItemImage::create(	"CloseNormal.png",
												"CloseSelected.png",
												CC_CALLBACK_1(CPauseLayer::resumeCallback, this));
	resumeButton->setScale(	buttonSize.width * 1.5f / resumeButton->getContentSize().width,
							buttonSize.height * 1.5f / resumeButton->getContentSize().height);
	resumeButton->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.5f));
	resumeButton->setColor(buttonColor);
	menuItemList.pushBack(resumeButton);
	
	// Create restart button
	auto restartButton = MenuItemImage::create(	"CloseNormal.png",
												"CloseSelected.png",
												CC_CALLBACK_1(CPauseLayer::restartCallback, this));
	restartButton->setScale(	buttonSize.width / restartButton->getContentSize().width,
							buttonSize.height / restartButton->getContentSize().height);
	restartButton->setPosition(resumeButton->getPosition() - Vec2(0, (resumeButton->getScaleY() * resumeButton->getContentSize().height) * 0.5f) + buttonPositionOffset);
	restartButton->setColor(buttonColor);
	menuItemList.pushBack(restartButton);
	
	// Create quit button
	auto quitButton = MenuItemImage::create("CloseNormal.png",
											"CloseSelected.png",
											CC_CALLBACK_1(CPauseLayer::quitCallback, this));
	quitButton->setScale(	buttonSize.width / quitButton->getContentSize().width,
							buttonSize.height / quitButton->getContentSize().height);
	quitButton->setPosition(restartButton->getPosition() - Vec2(0, (restartButton->getScaleY() * restartButton->getContentSize().height) * 0.5f) + buttonPositionOffset);
	quitButton->setColor(buttonColor);
	menuItemList.pushBack(quitButton);

    // Create menu
	auto menu = Menu::createWithArray(menuItemList);
	menu->setPosition(origin);
	menu->setTag(CHILD_TAG_MENU);
	this->addChild(menu, CHILD_TAG_MENU);



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
	this->getChildByTag(CHILD_TAG_MENU)->setPosition(offset);
	setVisible(true);
}

void CPauseLayer::resumeCallback(Ref* pSender)
{
	Director::getInstance()->resume();
	HideLayer();
}
void CPauseLayer::restartCallback(Ref* pSender)
{
	Director::getInstance()->resume();
	CGameStateManager::getInstance()->switchState(CGameStateManager::STATE_GAMEPLAY);
}
void CPauseLayer::quitCallback(Ref* pSender)
{
	Director::getInstance()->resume();
	CGameStateManager::getInstance()->switchState(CGameStateManager::STATE_MAINMENU);
}
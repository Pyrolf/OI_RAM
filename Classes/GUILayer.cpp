#include "GUILayer.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "PauseLayer.h"
#include "InGameScene.h"

USING_NS_CC;

CGUILayer* CGUILayer::addLayerToScene(Scene* scene)
{
    // 'layer' is an autorelease object
	auto layer = CGUILayer::create();
	layer->setName("CGUILayer");
    // add layer as a child to scene
	scene->addChild(layer);

	layer->m_pPauseLayer = CPauseLayer::addLayerToScene(scene);

	return layer;
}

// on "init" you need to initialize your instance
bool CGUILayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_vec2InitialCamPos = origin + Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f);

	// Create menu itmes
	Vector<MenuItem*> menuItemList;
	// Create Images
	auto coinImage = MenuItemImage::create(	"images/coin.png",
											"images/coin.png");
	coinImage->setScale(visibleSize.height * 0.075f / coinImage->getContentSize().height);
	coinImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	coinImage->setPosition(Vec2(origin.x + visibleSize.height * 0.025f,
								origin.y + visibleSize.height - visibleSize.height * 0.025f));
	menuItemList.pushBack(coinImage);
	// Create Labels
	std::stringstream ss;
	std::string font = "fonts/Marker Felt.ttf";
	float fontSize = visibleSize.height * 0.07f;

	ss << ": 0";
	auto coinsLabel = MenuItemLabel::create(Label::createWithTTF(ss.str(), font, fontSize));
	coinsLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	coinsLabel->setPosition(coinImage->getPosition() + Vec2(visibleSize.height * 0.08f, visibleSize.height * 0.005f));
	coinsLabel->setTag(COINS_CHILD_TAG_FOR_MENU);
	menuItemList.pushBack(coinsLabel);

	// Create Buttons
	// Create pause button
	auto pauseButton = MenuItemImage::create(	"images/ui/pause.png",
												"images/ui/pause_selected.png",
												CC_CALLBACK_1(CGUILayer::pauseCallback, this));
	pauseButton->setScale(0.75f);
	pauseButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	pauseButton->setPosition(Vec2(	origin.x + visibleSize.width - visibleSize.height * 0.01f,
									origin.y + visibleSize.height * 0.01f));
	menuItemList.pushBack(pauseButton);
	
    // Create menu
	auto menu = Menu::createWithArray(menuItemList);
	menu->setPosition(origin);
	menu->setTag(MENU_CHILD_TAG);
	this->addChild(menu, MENU_CHILD_TAG);

	HideLayer();

	return true;
}

void CGUILayer::HideLayer()
{
	setVisible(false);
}
void CGUILayer::ShowLayer(Vec2 offset)
{
	this->setPosition(offset);
	setVisible(true);
}

void CGUILayer::ChangeCoinsLabel(int coins)
{
	std::stringstream ss;
	ss << ": " << coins;
	auto menu = (Menu*)this->getChildByTag(MENU_CHILD_TAG);
	auto coinsLabel = (MenuItemLabel*)menu->getChildByTag(COINS_CHILD_TAG_FOR_MENU);
	coinsLabel->setString(ss.str());
}

void CGUILayer::pauseCallback(Ref* pSender)
{
	Director::getInstance()->pause();
	if (Director::getInstance()->getRunningScene()->getPhysicsWorld())
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
	m_pPauseLayer->ShowLayer(Camera::getDefaultCamera()->getPosition() - m_vec2InitialCamPos);
}
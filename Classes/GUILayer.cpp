#include "GUILayer.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "PauseLayer.h"

USING_NS_CC;

CGUILayer* CGUILayer::addLayerToScene(Scene* scene)
{
    // 'layer' is an autorelease object
    auto layer = CGUILayer::create();

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
	// Create Labels

	// Create Buttons
	Size buttonSize(visibleSize.width * 0.25f,
					visibleSize.height * 0.1f);
	Vec2 buttonPositionOffset(0, -visibleSize.height * 0.11f);
	Color3B buttonColor(Color3B::WHITE);
	// Create pause button
	auto pauseButton = MenuItemImage::create(	"CloseNormal.png",
												"CloseSelected.png",
												CC_CALLBACK_1(CGUILayer::pauseCallback, this));
	pauseButton->setScale(	buttonSize.height * 1.5f / pauseButton->getContentSize().width,
							buttonSize.height * 1.5f / pauseButton->getContentSize().height);
	pauseButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	pauseButton->setPosition(Vec2(	origin.x + visibleSize.width,
									origin.y));
	pauseButton->setColor(buttonColor);
	menuItemList.pushBack(pauseButton);
	
    // Create menu
	auto menu = Menu::createWithArray(menuItemList);
	menu->setPosition(origin);
	this->addChild(menu);

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

void CGUILayer::pauseCallback(Ref* pSender)
{
	Director::getInstance()->pause();
	if (Director::getInstance()->getRunningScene()->getPhysicsWorld())
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
	m_pPauseLayer->ShowLayer(Camera::getDefaultCamera()->getPosition() - m_vec2InitialCamPos);
}
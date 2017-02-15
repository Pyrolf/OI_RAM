#include "GUILayer.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "PauseLayer.h"
#include "InGameScene.h"
#include "SoundLoader.h"

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
	// Coins
	auto coinImage = MenuItemImage::create(	"images/coin.png",
											"images/coin.png");
	coinImage->setScale(visibleSize.height * 0.075f / coinImage->getContentSize().height);
	coinImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	coinImage->setPosition(Vec2(origin.x + visibleSize.height * 0.025f,
								origin.y + visibleSize.height - visibleSize.height * 0.025f));
	menuItemList.pushBack(coinImage);
	// Lives
	auto livesImage = MenuItemImage::create("images/heart.png",
											"images/heart.png");
	livesImage->setScale(visibleSize.height * 0.075f / livesImage->getContentSize().height);
	livesImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	livesImage->setPosition(Vec2(	origin.x + visibleSize.height * 0.025f,
									origin.y + visibleSize.height - visibleSize.height * 0.125f));
	menuItemList.pushBack(livesImage);
	// Mana
	auto manaImage = MenuItemImage::create(	"images/mana_potion.png",
											"images/mana_potion.png");
	manaImage->setScale(visibleSize.height * 0.075f / manaImage->getContentSize().height);
	manaImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	manaImage->setPosition(Vec2(origin.x + visibleSize.height * 0.025f,
								origin.y + visibleSize.height - visibleSize.height * 0.225f));
	menuItemList.pushBack(manaImage);
	// Manabar
	auto manabarSize = Size(visibleSize.width * 0.1f, visibleSize.height * 0.075f);
	// Manabar background
	auto manabarBackground = MenuItemImage::create(	"images/gray.png",
													"images/gray.png");
	manabarBackground->setScale(manabarSize.width / manabarBackground->getContentSize().width,
								manabarSize.height / manabarBackground->getContentSize().height);
	manabarBackground->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	manabarBackground->setPosition(manaImage->getPosition() + Vec2(visibleSize.height * 0.08f, 0));
	menuItemList.pushBack(manabarBackground);
	
	// Progress Timer
	// Manabar foreground
	auto manabarForeground = ProgressTimer::create(Sprite::create("images/blue.png"));
	manabarForeground->setType(ProgressTimer::Type::BAR);
	manabarForeground->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT);
	manabarForeground->setMidpoint(Vec2::ANCHOR_BOTTOM_LEFT);
	manabarForeground->setPercentage(0);
	manabarForeground->setScale(manabarSize.width / manabarForeground->getContentSize().width - manabarSize.width * 0.1f,
								manabarSize.height / manabarForeground->getContentSize().height - manabarSize.width * 0.1f);
	manabarForeground->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	manabarForeground->setPosition(manaImage->getPosition() + Vec2(visibleSize.height * 0.08f + manabarSize.width * 0.05f, -manabarSize.width * 0.05f));
	manabarForeground->setTag(MANA_CHILD_TAG);
	this->addChild(manabarForeground, MANA_CHILD_TAG);

	// Create Labels
	std::stringstream ss;
	std::string font = "fonts/Marker Felt.ttf";
	float fontSize = visibleSize.height * 0.07f;

	// Coins
	ss.str(": 0");
	auto coinsLabel = Label::createWithTTF(ss.str(), font, fontSize);
	coinsLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	coinsLabel->setPosition(coinImage->getPosition() + Vec2(visibleSize.height * 0.08f, visibleSize.height * 0.005f));
	coinsLabel->setTag(COINS_CHILD_TAG);
	this->addChild(coinsLabel, COINS_CHILD_TAG);
	// Lives
	auto livesLabel = Label::createWithTTF(ss.str(), font, fontSize);
	livesLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	livesLabel->setPosition(livesImage->getPosition() + Vec2(visibleSize.height * 0.08f, 0));
	livesLabel->setTag(LIVES_CHILD_TAG);
	this->addChild(livesLabel, LIVES_CHILD_TAG);

	// Create Buttons
	// Create pause button
	auto pauseButton = MenuItemImage::create(	"images/ui/pause.png",
												"images/ui/pause_selected.png",
												CC_CALLBACK_1(CGUILayer::pauseCallback, this));
	pauseButton->setScale(0.75f);
	pauseButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	pauseButton->setPosition(Vec2(	origin.x + visibleSize.width - visibleSize.height * 0.01f,
									origin.y + visibleSize.height * 0.01f));
	pauseButton->setTag(PAUSE_CHILD_TAG);
	menuItemList.pushBack(pauseButton);
	
    // Create menu
	auto menu = Menu::createWithArray(menuItemList);
	menu->setPosition(Vec2::ANCHOR_BOTTOM_LEFT);
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

void CGUILayer::PauseLayer(bool pause)
{
	auto pauseButton = (MenuItemImage*)this->getChildByTag(MENU_CHILD_TAG)->getChildByTag(PAUSE_CHILD_TAG);
	pauseButton->setEnabled(!pause);;
}

void CGUILayer::ChangeCoinsLabel(int coins)
{
	std::stringstream ss;
	ss << ": " << coins;
	auto coinsLabel = (Label*)this->getChildByTag(COINS_CHILD_TAG);
	coinsLabel->setString(ss.str());
}

void CGUILayer::ChangeLivesLabel(int lives)
{
	std::stringstream ss;
	ss << ": " << lives;
	auto livesLabel = (Label*)this->getChildByTag(LIVES_CHILD_TAG);
	livesLabel->setString(ss.str());
}

void CGUILayer::ChangeManabar(float percentage)
{
	auto manabar = (ProgressTimer*)this->getChildByTag(MANA_CHILD_TAG);
	// Finish unfinish action
	auto action = (FiniteTimeAction*)manabar->getActionByTag(MANABAR_ACTION_TAG);
	if (action)
	{
		action->step(action->getDuration());
	}
	// if current percentage is not equal to target
	if (manabar->getPercentage() != percentage)
	{
		float toChange = manabar->getPercentage() - percentage;
		if (toChange < 0)
			toChange = -toChange;
		float duration = 1.f;
		if (toChange != 100)
		{
			duration = 5.0f / toChange;
		}
		auto action = ProgressTo::create(duration, percentage);
		action->setTag(MANABAR_ACTION_TAG);
		manabar->runAction(action);
	}
}

void CGUILayer::pauseCallback(Ref* pSender)
{
	CSoundLoader::pauseSounds(true);
	CSoundLoader::playSoundEffect(CSoundLoader::PAUSE_SOUND_EFFECT);
	Director::getInstance()->pause();
	if (Director::getInstance()->getRunningScene()->getPhysicsWorld())
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
	m_pPauseLayer->ShowLayer(Camera::getDefaultCamera()->getPosition() - m_vec2InitialCamPos);
}
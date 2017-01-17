#include "StoreScene.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "SimpleAudioEngine.h"
#include "FileOperation.h"

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

	// Create menu itmes
	Vector<MenuItem*> menuItemList;

	// Create background
	auto background = MenuItemImage::create(	"HelloWorld.png",
												"HelloWorld.png");
	background->setScale(	visibleSize.width / background->getContentSize().width,
							visibleSize.height / background->getContentSize().height);
	background->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.5f));
	menuItemList.pushBack(background);
	
	// Coins Image
	auto coinImage = MenuItemImage::create(	"images/coin.png",
											"images/coin.png");
	coinImage->setScale(visibleSize.height * 0.075f / coinImage->getContentSize().height);
	coinImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	coinImage->setPosition(Vec2(origin.x + visibleSize.height * 0.025f,
								origin.y + visibleSize.height - visibleSize.height * 0.025f));
	menuItemList.pushBack(coinImage);

	// Create Labels
	std::string font = "fonts/Marker Felt.ttf";
	float fontSize = visibleSize.height * 0.05f;
	Color3B labelColor(Color3B::MAGENTA);

	// Create Title
	// Use label for now, may change to sprite image
	auto titleLabel = MenuItemLabel::create(Label::createWithTTF("STORE", "fonts/Marker Felt.ttf", visibleSize.height * 0.15f));
	titleLabel->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.9f));
	titleLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	titleLabel->setColor(labelColor);
	menuItemList.pushBack(titleLabel);

	// Coins
	auto coinsLabel = Label::createWithTTF(": 0", font, fontSize);
	coinsLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	coinsLabel->setPosition(coinImage->getPosition() + Vec2(visibleSize.height * 0.08f, visibleSize.height * 0.005f));
	coinsLabel->setTag(COINS_CHILD_TAG);
	this->addChild(coinsLabel, COINS_CHILD_TAG);

	// Create Buttons

	// Create Upgrade Buttons
	Size upgradeButtonSize(	visibleSize.width * 0.35f,
							visibleSize.height * 0.15f);
	Vec2 upgradeButtonPositionOffset(0, -visibleSize.height * 0.11f);
	//Color3B upgradeButtonColor(Color3B::YELLOW);

	// Create Upgrade Button Max Lives
	auto upgradeButtonMaxLives = MenuItemImage::create(	"images/ui/button.png",
														"images/ui/button_selected.png",
														CC_CALLBACK_1(CStoreScene::upgradeMaxLives, this));
	upgradeButtonMaxLives->setScale(upgradeButtonSize.width / upgradeButtonMaxLives->getContentSize().width,
									upgradeButtonSize.height / upgradeButtonMaxLives->getContentSize().height);
	upgradeButtonMaxLives->setPosition(Vec2(origin.x + visibleSize.width * 0.5f,
										origin.y + visibleSize.height * 0.6f));
	//upgradeButtonMaxLives->setColor(upgradeButtonColor);
	upgradeButtonMaxLives->setTag(LIVES_CHILD_TAG_FOR_MENU);
	menuItemList.pushBack(upgradeButtonMaxLives);
	// Upgrade label
	auto upgradeLabelMaxLives = MenuItemLabel::create(Label::createWithTTF("Upgrade Max Lives: 3", font, fontSize * 0.5f));
	upgradeLabelMaxLives->setPosition(Vec2(	upgradeButtonMaxLives->getContentSize().width * 0.5f,
											upgradeButtonMaxLives->getContentSize().height * 0.5f));
	upgradeLabelMaxLives->setColor(labelColor);
	upgradeLabelMaxLives->setTag(LIVES_CHILD_TAG_FOR_MENU);
	upgradeButtonMaxLives->addChild(upgradeLabelMaxLives);

	// Create Upgrade Button Max Mana
	auto upgradeButtonMaxMana = MenuItemImage::create(	"images/ui/button.png",
														"images/ui/button_selected.png",
														CC_CALLBACK_1(CStoreScene::upgradeMaxMana, this));
	upgradeButtonMaxMana->setScale(	upgradeButtonSize.width / upgradeButtonMaxMana->getContentSize().width,
									upgradeButtonSize.height / upgradeButtonMaxMana->getContentSize().height);
	upgradeButtonMaxMana->setPosition(upgradeButtonMaxLives->getPosition() - Vec2(0, upgradeButtonMaxLives->getContentSize().height * 0.5f) + upgradeButtonPositionOffset);
	//upgradeButtonMaxMana->setColor(upgradeButtonColor);
	upgradeButtonMaxMana->setTag(MANA_CHILD_TAG_FOR_MENU);
	menuItemList.pushBack(upgradeButtonMaxMana);
	// Upgrade label
	auto upgradeLabelMaxMana = MenuItemLabel::create(Label::createWithTTF("Upgrade Max Mana: 25", font, fontSize * 0.5f));
	upgradeLabelMaxMana->setPosition(Vec2(	upgradeButtonMaxMana->getContentSize().width * 0.5f,
											upgradeButtonMaxMana->getContentSize().height * 0.5f));
	upgradeLabelMaxMana->setColor(labelColor);
	upgradeLabelMaxMana->setTag(MANA_CHILD_TAG_FOR_MENU);
	upgradeButtonMaxMana->addChild(upgradeLabelMaxMana);

	// Create back to main menu button
	auto backToMainMenuButton = MenuItemImage::create(	"images/ui/back.png",
														"images/ui/back_selected.png",
														CC_CALLBACK_1(CStoreScene::backToMainMenuCallback, this));
	//backToMainMenuButton->setScale(	visibleSize.height * 0.15f / backToMainMenuButton->getContentSize().width,
	//								visibleSize.height * 0.15f / backToMainMenuButton->getContentSize().height);
	backToMainMenuButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	float offSet = visibleSize.height * 0.025f;
	backToMainMenuButton->setPosition(origin + Vec2(offSet, offSet));
	menuItemList.pushBack(backToMainMenuButton);

    // Create menu
	auto menu = Menu::createWithArray(menuItemList);
	menu->setPosition(origin);
	menu->setTag(MENU_CHILD_TAG);
	this->addChild(menu, MENU_CHILD_TAG);

	m_nCoins = 0;
	m_nLives = 3;
	m_nMana = 25;

	// Get Data
	getData();

    return true;
}


void CStoreScene::upgradeMaxLives(Ref* pSender)
{
	if (m_nLives >= 10 || !EditCoins(-10 * (m_nLives + 1)))
		return;
	m_nLives += 1;
	ChangeLivesLabel();
}
void CStoreScene::upgradeMaxMana(Ref* pSender)
{
	if (m_nMana >= 100 || !EditCoins(-2 * (m_nMana + 5)))
		return;
	m_nMana += 5;
	ChangeManaLabel();
}
void CStoreScene::backToMainMenuCallback(Ref* pSender)
{
	saveData();
	CGameStateManager::getInstance()->switchState(CGameStateManager::STATE_MAINMENU);
}

void CStoreScene::getData()
{
	// Get data Currency
	std::vector<std::string> vec_sData1 = FileOperation::readFile(FileOperation::CURRENCY_DATA_FILE_TYPE);
	if (vec_sData1.size() == 0)
		return;
	if (vec_sData1.size() > 0)
		EditCoins(std::stoi(vec_sData1[0]));

	// Get data Player
	std::vector<std::string> vec_sData2 = FileOperation::readFile(FileOperation::PLAYER_DATA_FILE_TYPE);
	if (vec_sData2.size() > 0)
	{
		m_nLives = std::stoi(vec_sData2[0]);
		ChangeLivesLabel();
	}
	if (vec_sData2.size() > 1)
	{
		m_nMana = std::stoi(vec_sData2[1]);
		ChangeManaLabel();
	}
}
void CStoreScene::saveData()
{
	// Save data
	std::stringstream ss1, ss2;

	ss1 << m_nCoins << "\n";
	FileOperation::saveFile(ss1.str(), FileOperation::CURRENCY_DATA_FILE_TYPE);

	ss2 << m_nLives << "\n";
	ss2 << m_nMana << "\n";
	FileOperation::saveFile(ss2.str(), FileOperation::PLAYER_DATA_FILE_TYPE);
}

bool CStoreScene::EditCoins(const int points)
{
	if ((int)m_nCoins + points < 0)
		return false;
	m_nCoins += points;
	ChangeCoinsLabel();
	return true;
}

void CStoreScene::ChangeCoinsLabel()
{
	std::stringstream ss;
	ss << ": " << m_nCoins;
	auto label = (Label*)this->getChildByTag(COINS_CHILD_TAG);
	label->setString(ss.str());
}

void CStoreScene::ChangeLivesLabel()
{
	std::stringstream ss;
	ss << "Upgrade Max Lives: " << m_nLives;
	auto menu = (Menu*)this->getChildByTag(MENU_CHILD_TAG);
	auto image = (MenuItemImage*)menu->getChildByTag(LIVES_CHILD_TAG_FOR_MENU);
	auto label = (MenuItemLabel*)image->getChildByTag(LIVES_CHILD_TAG_FOR_MENU);
	label->setString(ss.str());
}

void CStoreScene::ChangeManaLabel()
{
	std::stringstream ss;
	ss << "Upgrade Max Mana: " << m_nMana;
	auto menu = (Menu*)this->getChildByTag(MENU_CHILD_TAG);
	auto image = (MenuItemImage*)menu->getChildByTag(MANA_CHILD_TAG_FOR_MENU);
	auto label = (MenuItemLabel*)image->getChildByTag(MANA_CHILD_TAG_FOR_MENU);
	label->setString(ss.str());
}
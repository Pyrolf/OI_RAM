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

	// Create Title
	// Use label for now, may change to sprite image
	auto titleLabel = MenuItemLabel::create(Label::createWithTTF("STORE", "fonts/Marker Felt.ttf", visibleSize.height * 0.15f));
	titleLabel->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.9f));
	titleLabel->setColor(Color3B::MAGENTA);
	menuItemList.pushBack(titleLabel);

	// Create Labels
	std::stringstream ss;
	std::string font = "fonts/Marker Felt.ttf";
	float fontSize = visibleSize.height * 0.05f;

	ss << "Points: 0";
	auto pointsLabel = MenuItemLabel::create(Label::createWithTTF(ss.str(), font, fontSize));
	pointsLabel->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	pointsLabel->setPosition(Vec2(	origin.x + visibleSize.width - visibleSize.height * 0.05f,
									origin.y + visibleSize.height - visibleSize.height * 0.05f));
	pointsLabel->setTag(POINTS_CHILD_TAG_FOR_MENU);
	menuItemList.pushBack(pointsLabel);

	// Create Buttons
	// Create Upgrade Buttons
	Size upgradeButtonSize(	visibleSize.width * 0.35f,
							visibleSize.height * 0.15f);
	Vec2 upgradeButtonPositionOffset(0, -visibleSize.height * 0.11f);
	Color3B upgradeButtonColor(Color3B::YELLOW);
	// Create Upgrade Button 1
	auto upgradeButton1 = MenuItemImage::create("CloseNormal.png",
												"CloseSelected.png",
												CC_CALLBACK_1(CStoreScene::upgradeOne, this));
	upgradeButton1->setScale(	upgradeButtonSize.width / upgradeButton1->getContentSize().width,
								upgradeButtonSize.height / upgradeButton1->getContentSize().height);
	upgradeButton1->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
										origin.y + visibleSize.height * 0.6f));
	upgradeButton1->setColor(upgradeButtonColor);
	menuItemList.pushBack(upgradeButton1);
	// Create Upgrade Button 2
	auto upgradeButton2 = MenuItemImage::create("CloseNormal.png",
												"CloseSelected.png",
												CC_CALLBACK_1(CStoreScene::upgradeOne, this));
	upgradeButton2->setScale(	upgradeButtonSize.width / upgradeButton2->getContentSize().width,
								upgradeButtonSize.height / upgradeButton2->getContentSize().height);
	upgradeButton2->setPosition(upgradeButton1->getPosition() - Vec2(0, upgradeButtonSize.height * 0.5f) + upgradeButtonPositionOffset);
	upgradeButton2->setColor(upgradeButtonColor);
	menuItemList.pushBack(upgradeButton2);

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
	menu->setTag(MENU_CHILD_TAG);
	this->addChild(menu, MENU_CHILD_TAG);

	m_nPoints = 0;

	// Get Data
	getData();

    return true;
}


void CStoreScene::upgradeOne(Ref* pSender)
{

}
void CStoreScene::backToMainMenuCallback(Ref* pSender)
{
	saveData();
	CGameStateManager::getInstance()->switchState(CGameStateManager::STATE_MAINMENU);
}

void CStoreScene::getData()
{
	std::vector<std::string> vec_sData = FileOperation::readFile(FileOperation::CURRENCY_DATA_FILE_TYPE);
	if (vec_sData.size() == 0)
		return;
	// Get data
	EditPoints(std::stoi(vec_sData[0]));
}
void CStoreScene::saveData()
{
	// Save data
	std::stringstream ss;

	ss << m_nPoints << "\n";
	FileOperation::saveFile(ss.str(), FileOperation::CURRENCY_DATA_FILE_TYPE);
}

void CStoreScene::EditPoints(const unsigned int points)
{
	m_nPoints += points;
	ChangePointsLabel();
}

void CStoreScene::ChangePointsLabel()
{
	std::stringstream ss;
	ss << "Points: " << m_nPoints;
	auto menu = (Menu*)this->getChildByTag(MENU_CHILD_TAG);
	auto pointsLabel = (MenuItemLabel*)menu->getChildByTag(POINTS_CHILD_TAG_FOR_MENU);
	pointsLabel->setString(ss.str());
}
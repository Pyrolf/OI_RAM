#include "MainMenuScene.h"
#include "AnimationSystem.h"
#include "SpriteSystem.h"
#include "GameStateManager.h"
#include "FileOperation.h"
#include "SoundLoader.h"

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

	// Label
	std::string font = "fonts/Marker Felt.ttf";
	float fontSize = visibleSize.height * 0.05f;
	Color3B labelColor(Color3B::MAGENTA);

	// Create menu itmes
	Vector<MenuItem*> menuItemList;
	
	// Create background
	auto background = MenuItemImage::create(	"images/ui/background1.png",
												"images/ui/background1.png");
	background->setScale(	visibleSize.width / background->getContentSize().width,
							visibleSize.height / background->getContentSize().height);
	background->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.5f));
	menuItemList.pushBack(background);

	// Create Title
	// Use label for now, may change to sprite image
	auto titleLabel = Label::createWithTTF("OI-RAM!", font, visibleSize.height * 0.25f);
	titleLabel->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.8f));
	titleLabel->setColor(labelColor);
	titleLabel->setTag(CHILD_TAG_LABEL);
	this->addChild(titleLabel, CHILD_TAG_LABEL);

	// Create buttons
	Size toggleButtonSize(	visibleSize.height * 0.1f,
							visibleSize.height * 0.1f);
	Vec2 buttonPositionOffset(0, -visibleSize.height * 0.15f);
	// Create start button
	auto startButton = MenuItemImage::create(	"images/ui/button.png",
												"images/ui/button_selected.png",
												CC_CALLBACK_1(CMainMenuScene::startGameCallback, this));
	/*startButton->setScale(	buttonSize.width * 1.5f / startButton->getContentSize().width,
							buttonSize.height * 1.5f / startButton->getContentSize().height);*/
	startButton->setScale(1.5f);
	startButton->setPosition(Vec2(	origin.x + visibleSize.width * 0.5f,
									origin.y + visibleSize.height * 0.4f));
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
	
	// Music toggle button
	auto musicToggleButton = MenuItemImage::create(	"images/ui/music_toggle.png",
													"images/ui/music_toggle_selected.png",
													CC_CALLBACK_1(CMainMenuScene::toggleMusicCallback, this));
	musicToggleButton->setScale(	toggleButtonSize.width / musicToggleButton->getContentSize().width,
									toggleButtonSize.height / musicToggleButton->getContentSize().height);
	musicToggleButton->setPosition(	origin.x + visibleSize.width - toggleButtonSize.width * 2.0f,
									origin.y + visibleSize.height - toggleButtonSize.width * 0.75f);
	musicToggleButton->setTag(CHILD_TAG_MUSIC_TOGGLE_BUTTON);
	menuItemList.pushBack(musicToggleButton);
	
	// Sound Effect toggle button
	auto soundEffectToggleButton = MenuItemImage::create(	"images/ui/sound_effects_toggle.png",
															"images/ui/sound_effects_toggle_selected.png",
															CC_CALLBACK_1(CMainMenuScene::toggleSoundEffectsCallback, this));
	soundEffectToggleButton->setScale(	toggleButtonSize.width / soundEffectToggleButton->getContentSize().width,
										toggleButtonSize.height / soundEffectToggleButton->getContentSize().height);
	soundEffectToggleButton->setPosition(	origin.x + visibleSize.width - toggleButtonSize.width * 0.75f,
											origin.y + visibleSize.height - toggleButtonSize.width * 0.75f);
	soundEffectToggleButton->setTag(CHILD_TAG_SOUND_EFFECT_TOGGLE_BUTTON);
	menuItemList.pushBack(soundEffectToggleButton);

    // Create menu
	auto menu = Menu::createWithArray(menuItemList);
	menu->setPosition(Vec2::ANCHOR_BOTTOM_LEFT);
	menu->setTag(CHILD_TAG_MENU);
	this->addChild(menu, CHILD_TAG_MENU);

	m_bMusicMuted = false;
	m_bSoundEffectsMuted = false;
	getSettingsData();

    return true;
}

void CMainMenuScene::startGameCallback(Ref* pSender)
{
	CSoundLoader::playSoundEffect(CSoundLoader::SELECT_SOUND_EFFECT);

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
	CSoundLoader::playSoundEffect(CSoundLoader::SELECT_SOUND_EFFECT);

	CGameStateManager::getInstance()->switchState(CGameStateManager::STATE_STORE);
}
void CMainMenuScene::exitGameCallback(Ref* pSender)
{
	CSoundLoader::playSoundEffect(CSoundLoader::SELECT_SOUND_EFFECT);

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void CMainMenuScene::toggleMusicCallback(cocos2d::Ref* pSender)
{
	m_bMusicMuted = !m_bMusicMuted;
	setSettingsData();
	toggleMusicButtonImage();
	CSoundLoader::muteBackgroundMusic(m_bMusicMuted);
	CSoundLoader::playSoundEffect(CSoundLoader::PAUSE_SOUND_EFFECT);
}

void CMainMenuScene::toggleSoundEffectsCallback(cocos2d::Ref* pSender)
{
	m_bSoundEffectsMuted = !m_bSoundEffectsMuted;
	setSettingsData();
	toggleSoundEffectsButtonImage();
	CSoundLoader::muteSoundEffect(m_bSoundEffectsMuted);
	CSoundLoader::playSoundEffect(CSoundLoader::PAUSE_SOUND_EFFECT);
}

void CMainMenuScene::getSettingsData()
{
	// Get data Currency
	std::vector<std::string> vec_sData1 = FileOperation::readFile(FileOperation::SETTINGS_DATA_FILE_TYPE);
	if (vec_sData1.size() == 0)
		return;
	if (vec_sData1.size() > 0)
	{
		if (std::stoi(vec_sData1[0]) > 0)
		{
			m_bMusicMuted = true;
			toggleMusicButtonImage();
			CSoundLoader::muteBackgroundMusic(m_bMusicMuted);
		}
		else
			m_bMusicMuted = false;
	}
	if (vec_sData1.size() > 1)
	{
		if (std::stoi(vec_sData1[1]) > 0)
		{
			m_bSoundEffectsMuted = true;
			toggleSoundEffectsButtonImage();
			CSoundLoader::muteSoundEffect(m_bSoundEffectsMuted);
		}
		else
			m_bSoundEffectsMuted = false;
	}
}

void CMainMenuScene::setSettingsData()
{
	// Save data
	std::stringstream ss1;

	ss1 << m_bMusicMuted << "\n";
	ss1 << m_bSoundEffectsMuted << "\n";
	FileOperation::saveFile(ss1.str(), FileOperation::SETTINGS_DATA_FILE_TYPE);
}

void CMainMenuScene::toggleMusicButtonImage()
{
	auto button = (MenuItemImage*)this->getChildByTag(CHILD_TAG_MENU)->getChildByTag(CHILD_TAG_MUSIC_TOGGLE_BUTTON);
	const std::string UNPRESSED = (m_bMusicMuted) ? "images/ui/music_toggle_muted_selected.png" : "images/ui/music_toggle_selected.png";
	const std::string PRESSED = (m_bMusicMuted) ? "images/ui/music_toggle_muted.png" : "images/ui/music_toggle.png";

	button->setSelectedImage(Sprite::create(UNPRESSED));
	button->setNormalImage(Sprite::create(PRESSED));
}
void CMainMenuScene::toggleSoundEffectsButtonImage()
{
	auto button = (MenuItemImage*)this->getChildByTag(CHILD_TAG_MENU)->getChildByTag(CHILD_TAG_SOUND_EFFECT_TOGGLE_BUTTON);
	const std::string UNPRESSED = (m_bSoundEffectsMuted) ? "images/ui/sound_effects_toggle_muted_selected.png" : "images/ui/sound_effects_toggle_selected.png";
	const std::string PRESSED = (m_bSoundEffectsMuted) ? "images/ui/sound_effects_toggle_muted.png" : "images/ui/sound_effects_toggle.png";

	button->setSelectedImage(Sprite::create(UNPRESSED));
	button->setNormalImage(Sprite::create(PRESSED));
}
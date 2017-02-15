#include "GameStateManager.h"
#include "MainMenuScene.h"
#include "InGameScene.h"
#include "StoreScene.h"
#include "SoundLoader.h"

USING_NS_CC;

CGameStateManager* CGameStateManager::s_gameStateManagerInstance = NULL;

CGameStateManager::CGameStateManager()
	: m_eState(STATE_NIL)
{
}

CGameStateManager::~CGameStateManager()
{
}

// Instance Methods
CGameStateManager* CGameStateManager::getInstance()
{
	if (!s_gameStateManagerInstance)
		s_gameStateManagerInstance = new CGameStateManager;
	return s_gameStateManagerInstance;
}

void CGameStateManager::destroy()
{
	if (s_gameStateManagerInstance)
		delete s_gameStateManagerInstance;
	s_gameStateManagerInstance = NULL;
}

// Normal Methods
// Public Methods
void CGameStateManager::switchState(CGameStateManager::STATE state)
{
	m_eState = state;
	switch (state)
	{
		case STATE_MAINMENU:
		{
			CMainMenuScene::toMainMenuScene();
			CSoundLoader::playBackgroundMusic(CSoundLoader::BACKGROUND_MUSIC::MAIN_MENU_MUSIC);
			break;
		}
		case STATE_GAMEPLAY:
		{
			CInGameScene::toInGameScene();
			CSoundLoader::playBackgroundMusic(CSoundLoader::BACKGROUND_MUSIC::GAMEPLAY_MUSIC);
			break;
		}
		case STATE_STORE:
		{
			CStoreScene::toStoreScene();
			CSoundLoader::playBackgroundMusic(CSoundLoader::BACKGROUND_MUSIC::STORE_MUSIC);
			break;
		}
		default:
		{
			CMainMenuScene::toMainMenuScene();
			break;
		}
	}
}
CGameStateManager::STATE CGameStateManager::getState()
{
	return m_eState;
}
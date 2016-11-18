#include "GameStateManager.h"
#include "MainMenuScene.h"
#include "InGameScene.h"
#include "StoreScene.h"

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
			break;
		}
		case STATE_GAMEPLAY:
		{
			CInGameScene::toInGameScene();
			break;
		}
		case STATE_STORE:
		{
			CStoreScene::toStoreScene();
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
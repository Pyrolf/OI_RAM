#ifndef __GAME_STATE_MANAGER_H__
#define __GAME_STATE_MANAGER_H__

#include "cocos2d.h"

class CGameStateManager
{
public:
	enum STATE
	{
		STATE_NIL = 0,
		STATE_MAINMENU,
		STATE_GAMEPLAY,
		STATE_PAUSE,
		STATE_STORE,
		NUM_OF_STATE
	};
private:
	static CGameStateManager* s_gameStateManagerInstance;
	CGameStateManager();
	~CGameStateManager();

	STATE m_eState;
public:
	// Instance Methods
	static CGameStateManager* getInstance();
	static void destroy();

	// Normal Methods
	void switchState(STATE state);
	STATE getState();
};

#endif // __GAME_STATE_MANAGER_H__

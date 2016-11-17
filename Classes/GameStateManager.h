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
		NUM_OF_STATE
	};
private:
	static CGameStateManager* s_gameStateManagerInstance;
	CGameStateManager();
	~CGameStateManager();

	std::vector<STATE> m_eStates;
public:
	// Instance Methods
	static CGameStateManager* getInstance();
	static void destroy();

	// Normal Methods
	void startState(STATE state);
	void switchState(STATE state);
	void pushState(STATE state);
	STATE popState();
	STATE getCurrentState();
};

#endif // __GAME_STATE_MANAGER_H__

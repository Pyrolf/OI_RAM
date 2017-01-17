#ifndef __INGAME_SCENE_H__
#define __INGAME_SCENE_H__

class CGUILayer;
class CWonOrGameoverLayer;

#include "cocos2d.h"
#include "TilemapManager.h"
#include "KeyboardManager.h"
#include "Player.h"
#include "GameObjectManager.h"

class CInGameScene : public cocos2d::Layer
{
private:
	CGUILayer* m_pGUILayer;
	CWonOrGameoverLayer* m_pWonOrGameoverLayer;

	enum CHILD_TAG
	{
		CHILD_TAG_BACKGROUND = 0,
		CHILD_TAG_GAMEOBJECT,
		NUM_OF_CHILD_TAGS = CHILD_TAG_GAMEOBJECT + 4
	};
public:
	~CInGameScene();

    static cocos2d::Scene* createScene();
	static void toInGameScene();

	virtual bool init();
	void initGameObjects();

	virtual void onEnterTransitionDidFinish();

	virtual void update(float);

    // selector callback

    // implement the "static create()" method manually
	CREATE_FUNC(CInGameScene);

	void AddCoins(const unsigned int coins);
	void AddCoinsToLabel();

	void AddLives(const unsigned int lives);
	void AddLivesToLabel();

	void AddMana(const int mana);
	void AddManaToBar();

	void ReachExit();

	bool IfLastLevel();
	void NextLevel();

	void endScene(bool bSave = false);
private:
	KeyboardManager* KBM;

	TilemapManager* tileMapManager;

	CGameObjectManager* m_pGOManager;

	unsigned int m_nCoins;
	unsigned int m_nCoinsAddedToLabel;

	unsigned int m_nLives;
	unsigned int m_nLivesAddedToLabel;

	unsigned int m_nMana;
	unsigned int m_nManaMaxCap;
	unsigned int m_nManaAddedToBar;

	unsigned int m_nCurrentLevel;
	unsigned int m_nMaxLevel;


	void getMapData();
	void getData();
	void saveData();
};

#endif // __INGAME_SCENE_H__

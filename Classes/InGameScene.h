#ifndef __INGAME_SCENE_H__
#define __INGAME_SCENE_H__

class CGUILayer;

#include "cocos2d.h"
#include "TilemapManager.h"
#include "KeyboardManager.h"
#include "Player.h"
#include "GameObjectManager.h"

class CInGameScene : public cocos2d::Layer
{
private:
	CGUILayer* m_pGUILayer;

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

	virtual void update(float);

    // selector callback

    // implement the "static create()" method manually
	CREATE_FUNC(CInGameScene);

private:
	KeyboardManager* KBM;

	TilemapManager* tileMapManager;

	Player* player;

	CGameObjectManager* m_pGOManager;

	void getData();
	void saveData();
};

#endif // __INGAME_SCENE_H__

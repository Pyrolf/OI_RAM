#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class CMainMenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static void toMainMenuScene();

	virtual bool init();

    // Selector callbacks
	void startGameCallback(cocos2d::Ref* pSender);
	void goStoreCallback(cocos2d::Ref* pSender);
    void exitGameCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(CMainMenuScene);
private:
	enum CHILD_TAG
	{
		CHILD_TAG_BACKGROUND = 0,
		CHILD_TAG_MENU,
		NUM_OF_CHILD_TAGS
	};
};

#endif // __MAINMENU_SCENE_H__

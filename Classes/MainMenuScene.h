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
	void toggleMusicCallback(cocos2d::Ref* pSender);
	void toggleSoundEffectsCallback(cocos2d::Ref* pSender);
    
	void getSettingsData();
	void setSettingsData();

	void toggleMusicButtonImage();
	void toggleSoundEffectsButtonImage();

    // implement the "static create()" method manually
	CREATE_FUNC(CMainMenuScene);
private:
	enum CHILD_TAG
	{
		CHILD_TAG_MENU = 0,
		CHILD_TAG_LABEL,
		CHILD_TAG_MUSIC_TOGGLE_BUTTON,
		CHILD_TAG_SOUND_EFFECT_TOGGLE_BUTTON,
		NUM_OF_CHILD_TAGS
	};

	bool m_bMusicMuted;
	bool m_bSoundEffectsMuted;
};

#endif // __MAINMENU_SCENE_H__

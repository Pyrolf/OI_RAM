#ifndef __GUI_LAYER_H__
#define __GUI_LAYER_H__

class CPauseLayer;

#include "cocos2d.h"

class CGUILayer : public cocos2d::Layer
{
private:
	enum ACTION_TAG
	{
		MANABAR_ACTION_TAG = 0,
		NUM_OF_ACTION_TAGS
	};
	enum CHILD_TAG
	{
		MENU_CHILD_TAG = 0,
		COINS_CHILD_TAG,
		LIVES_CHILD_TAG,
		MANA_CHILD_TAG,
		NUM_OF_CHILD_TAGS
	};
	CPauseLayer* m_pPauseLayer;
	cocos2d::Vec2 m_vec2InitialCamPos;
public:
	static CGUILayer* addLayerToScene(cocos2d::Scene* scene);

	virtual bool init();

	void HideLayer();
	void ShowLayer(cocos2d::Vec2 offset);

	void ChangeCoinsLabel(int coins);
	void ChangeLivesLabel(int lives);
	void ChangeManabar(float percentage);

    // selector callbacks
	void pauseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(CGUILayer);

	// Getters
	cocos2d::Vec2 GetInitialCamPos(){ return m_vec2InitialCamPos; }
};

#endif // __GUI_LAYER_H__

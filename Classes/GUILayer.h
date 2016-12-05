#ifndef __GUI_LAYER_H__
#define __GUI_LAYER_H__

class CPauseLayer;

#include "cocos2d.h"

class CGUILayer : public cocos2d::Layer
{
private:
	enum CHILD_TAG
	{
		MENU_CHILD_TAG = 0,
		NUM_OF_CHILD_TAGS
	};
	enum CHILD_TAG_FOR_MENU
	{
		POINTS_CHILD_TAG_FOR_MENU = 0,
		NUM_OF_CHILD_TAGS_FOR_MENU
	};
	CPauseLayer* m_pPauseLayer;
	cocos2d::Vec2 m_vec2InitialCamPos;
public:
	static CGUILayer* addLayerToScene(cocos2d::Scene* scene);

	virtual bool init();

	void HideLayer();
	void ShowLayer(cocos2d::Vec2 offset);

	void ChangePointsLabel(int points);

    // selector callbacks
	void pauseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(CGUILayer);

	// Getters
	cocos2d::Vec2 GetInitialCamPos(){ return m_vec2InitialCamPos; }
};

#endif // __GUI_LAYER_H__

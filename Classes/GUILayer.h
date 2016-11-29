#ifndef __GUI_LAYER_H__
#define __GUI_LAYER_H__

class CPauseLayer;

#include "cocos2d.h"

class CGUILayer : public cocos2d::Layer
{
private:
	enum CHILD_TAG
	{
		CHILD_TAG_BACKGROUND = 0,
		CHILD_TAG_MENU,
		NUM_OF_CHILD_TAGS
	};

	CPauseLayer* m_pPauseLayer;
	cocos2d::Vec2 m_vec2InitialCamPos;
public:
	static CGUILayer* addLayerToScene(cocos2d::Scene* scene);

	virtual bool init();

	void HideLayer();
	void ShowLayer(cocos2d::Vec2 offset);

    // selector callbacks
	void pauseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(CGUILayer);
};

#endif // __GUI_LAYER_H__

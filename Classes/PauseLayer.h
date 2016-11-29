#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

class CPauseLayer : public cocos2d::Layer
{
public:
	static CPauseLayer* addLayerToScene(cocos2d::Scene* scene);

	virtual bool init();

	void HideLayer();
	void ShowLayer(cocos2d::Vec2 offset);

    // selector callbacks
	void resumeCallback(cocos2d::Ref* pSender);
	void restartCallback(cocos2d::Ref* pSender);
	void quitCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(CPauseLayer);
};

#endif // __PAUSE_LAYER_H__

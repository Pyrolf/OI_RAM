#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

class CPauseLayer : public cocos2d::Layer
{
private:
	enum CHILD_TAG
	{
		CHILD_TAG_BACKGROUND = 0,
		CHILD_TAG_MENU,
		NUM_OF_CHILD_TAGS
	};
public:
	static CPauseLayer* addLayerToScene(cocos2d::Scene* scene);

	virtual bool init();

	void HideLayer();
	void ShowLayer();

    // selector callbacks
	void resumeCallback(cocos2d::Ref* pSender);
	void restartCallback(cocos2d::Ref* pSender);
	void quitCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(CPauseLayer);
};

#endif // __PAUSE_LAYER_H__

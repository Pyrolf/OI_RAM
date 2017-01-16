#ifndef __WON_OR_GAMEOVER_LAYER_H__
#define __WON_OR_GAMEOVER_LAYER_H__

#include "cocos2d.h"

class CWonOrGameoverLayer : public cocos2d::Layer
{
private:
	enum CHILD_TAG
	{
		CHILD_TAG_MENU = 0,
		CHILD_TAG_WON_LABEL,
		CHILD_TAG_GAMEOVER_LABEL,
		CHILD_TAG_NEXT_LEVEL_BUTTON,
		NUM_OF_CHILD_TAGS
	};
public:
	static CWonOrGameoverLayer* addLayerToScene(cocos2d::Scene* scene);

	virtual bool init();

	void HideLayer();
	void ShowLayer(cocos2d::Vec2 offset, bool showWin);

    // selector callbacks
	void nextLevelCallback(cocos2d::Ref* pSender);
	void restartCallback(cocos2d::Ref* pSender);
	void quitCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(CWonOrGameoverLayer);
};

#endif // __WINNING_OR_LOSING_LAYER_H__

#ifndef __INGAME_SCENE_H__
#define __INGAME_SCENE_H__

#include "cocos2d.h"

class CInGameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	static void toInGameScene();

	virtual bool init();

	virtual void update(float);

    // a selector callback
	void backToMainMenuCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(CInGameScene);
};

#endif // __INGAME_SCENE_H__

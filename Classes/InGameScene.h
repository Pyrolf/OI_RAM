#ifndef __INGAME_SCENE_H__
#define __INGAME_SCENE_H__

class CPauseLayer;

#include "cocos2d.h"

class CInGameScene : public cocos2d::Layer
{
private:
	CPauseLayer* m_pPauseLayer;
public:
    static cocos2d::Scene* createScene();
	static void toInGameScene();

	virtual bool init();
	void initPause();

	virtual void update(float);

    // selector callback
	void pauseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(CInGameScene);
};

#endif // __INGAME_SCENE_H__

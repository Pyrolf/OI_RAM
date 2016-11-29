#ifndef __INGAME_SCENE_H__
#define __INGAME_SCENE_H__

class CGUILayer;

#include "cocos2d.h"

class CInGameScene : public cocos2d::Layer
{
private:
	CGUILayer* m_pGUILayer;
public:
    static cocos2d::Scene* createScene();
	static void toInGameScene();

	virtual bool init();

	virtual void update(float);

    // selector callback
    
    // implement the "static create()" method manually
	CREATE_FUNC(CInGameScene);
};

#endif // __INGAME_SCENE_H__

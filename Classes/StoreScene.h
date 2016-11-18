#ifndef __STORE_SCENE_H__
#define __STORE_SCENE_H__

#include "cocos2d.h"

class CStoreScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static void toStoreScene();

	virtual bool init();

    // Selector callbacks
	void backToMainMenuCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
	CREATE_FUNC(CStoreScene);
private:
	enum CHILD_TAG
	{
		CHILD_TAG_BACKGROUND = 0,
		CHILD_TAG_MENU,
		NUM_OF_CHILD_TAGS
	};
};

#endif // __STORE_SCENE_H__

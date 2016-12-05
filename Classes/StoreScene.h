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
	void upgradeOne(cocos2d::Ref* pSender);
	void backToMainMenuCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
	CREATE_FUNC(CStoreScene);
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

	void getData();
	void saveData();

	unsigned int m_nPoints;
	void EditPoints(const unsigned int points);
	void ChangePointsLabel();
};

#endif // __STORE_SCENE_H__

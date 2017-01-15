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
	void upgradeMaxLives(cocos2d::Ref* pSender);
	void upgradeMaxMana(cocos2d::Ref* pSender);
	void backToMainMenuCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
	CREATE_FUNC(CStoreScene);
private:
	enum CHILD_TAG
	{
		MENU_CHILD_TAG = 0,
		COINS_CHILD_TAG,
		LIVES_CHILD_TAG_FOR_MENU,
		MANA_CHILD_TAG_FOR_MENU,
		NUM_OF_CHILD_TAGS
	};

	void getData();
	void saveData();

	unsigned int m_nCoins;
	unsigned int m_nLives;
	unsigned int m_nMana;

	bool EditCoins(const int coins);
	void ChangeCoinsLabel();
	void ChangeLivesLabel();
	void ChangeManaLabel();
};

#endif // __STORE_SCENE_H__

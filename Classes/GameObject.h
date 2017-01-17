#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "cocos2d.h"

class CGameObject : public cocos2d::Node
{
public:
	CGameObject();
	virtual ~CGameObject();

	static CGameObject* create();
	virtual void MinusLives(int nDamage);

	// Setters
	void SetSprite(cocos2d::Sprite* sprite, cocos2d::Size size);
	void SetSpriteSize(cocos2d::Size spriteSize) { m_spriteSize = spriteSize; }
	void SetActive(bool bActive) { m_bActive = bActive; }
	void SetLives(int nLives) { m_nLives = nLives; }
	// Getters
	cocos2d::Sprite* GetSprite() { return m_pSprite; }
	cocos2d::Size GetSpriteSize() { return m_spriteSize; }
	bool GetActive() { return m_bActive; }
	int GetLives() { return m_nLives; }
private:
	cocos2d::Sprite* m_pSprite;
	cocos2d::Size m_spriteSize;
	bool m_bActive;
	int m_nLives;
};

#endif // __GAME_OBJECT_H__
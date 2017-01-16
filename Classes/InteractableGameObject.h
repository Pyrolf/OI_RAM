#ifndef __INTERACTABLE_GAME_OBJECT_H__
#define __INTERACTABLE_GAME_OBJECT_H__

#include "GameObject.h"

class CInteractableGameObject : public CGameObject
{
public:
	CInteractableGameObject();
	virtual ~CInteractableGameObject();

	static CInteractableGameObject* create();

	enum TYPE
	{
		COIN = 0,
		LIVE,
		MANA_POTION,
		EXIT,
		NUM_OF_TYPES
	};

	virtual bool CheckCollision();


	// Setters
	void SetType(TYPE eType) { m_eType = eType; }
	void SetTargetGO(CGameObject* pTargetGO) { m_pTargetGO = pTargetGO; }
	// Getters
	TYPE GetType() { return m_eType; }
	CGameObject* GetTargetGO() { return m_pTargetGO; }
private:
	TYPE m_eType;
	CGameObject* m_pTargetGO;
};


class CCoin : public CInteractableGameObject
{
public:
	CCoin();
	virtual ~CCoin();

	//virtual bool CheckCollision(cocos2d::Rect tragetRect);
};

#endif // __INTERACTABLE_GAME_OBJECT_H__
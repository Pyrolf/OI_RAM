#pragma once

#include "GameObject.h"

class CPhysicsGameObject : public CGameObject
{
public:
	CPhysicsGameObject();
	virtual ~CPhysicsGameObject();

	static CPhysicsGameObject* create();

	enum TYPE
	{
		CRATE = 0,
		JUMPPAD,
		NUM_OF_TYPES
	};

	// Setters
	void SetType(TYPE eType) { type = eType; }
	// Getters
	TYPE GetType() { return type; }

	void GeneratePhysicsBody();

	void DestroyCrate();
private:
	TYPE type;
};
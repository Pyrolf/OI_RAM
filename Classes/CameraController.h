#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class CameraController : public Node
{
public:
	enum CAM_STATE
	{
		C_STATIC,
		C_FREE_CAM,
		C_FOLLOW
	};

	CameraController();
	~CameraController();

	virtual void update(float);

	void setStatic();
	void setFreeMovement(float speed);
	void setFollowTarget(Node* target);

	CAM_STATE getState() { return state; };

private:
	Camera* mainCam;

	CAM_STATE state;

	float followSpeed;

	Node* target;
};
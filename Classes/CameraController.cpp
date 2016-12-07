#include "CameraController.h"
#include "KeyboardManager.h"

CameraController::CameraController()
{
	mainCam = Director::getInstance()->getRunningScene()->getDefaultCamera();

	setStatic();

	this->scheduleUpdate();
}


CameraController::~CameraController()
{
}

void CameraController::update(float dt)
{
	mainCam = Director::getInstance()->getRunningScene()->getDefaultCamera();
	switch (state)
	{
	case C_FREE_CAM:
		if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_A))
		{
			mainCam->setPosition(mainCam->getPositionX() - dt * followSpeed, mainCam->getPositionY());
		}
		if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_D))
		{
			mainCam->setPosition(mainCam->getPositionX() + dt * followSpeed, mainCam->getPositionY());
		}
		if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) && KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_W))
		{
			mainCam->setPosition(mainCam->getPositionX(), mainCam->getPositionY() + dt * followSpeed);
		}
		if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_S))
		{
			mainCam->setPosition(mainCam->getPositionX(), mainCam->getPositionY() - dt * followSpeed);
		}
		break;

	case C_FOLLOW:
		{
			Vec2 dir = target->getPosition() - mainCam->getPosition();
			float magnitude = dir.length();
			dir.normalize();

			mainCam->setPosition(mainCam->getPosition() + (dir * magnitude) * dt * 5);
		}
		break;
	}
}


void CameraController::setStatic()
{
	state = C_STATIC;
}

void CameraController::setFreeMovement(float speed)
{
	state = C_FREE_CAM;
	followSpeed = speed;
}

void CameraController::setFollowTarget(Node* target)
{
	state = C_FOLLOW;
	this->target = target;
}
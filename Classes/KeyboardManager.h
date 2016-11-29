#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class KeyboardManager : public cocos2d::Node
{
public:
	KeyboardManager();
	~KeyboardManager();
	
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

	double keyPressedDuration(EventKeyboard::KeyCode code);

private:
	//container of all keys that are pressed
	std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;
};


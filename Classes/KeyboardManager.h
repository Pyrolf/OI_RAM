#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class KeyboardManager : public Node
{
public:
	static KeyboardManager* GetInstance();

	static void Destroy();

	~KeyboardManager();
	
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

	double keyPressedDuration(EventKeyboard::KeyCode code);

	void removeKey(cocos2d::EventKeyboard::KeyCode);

private:
	KeyboardManager();
	
	static KeyboardManager* instance;

	//container of all keys that are pressed
	std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;
};


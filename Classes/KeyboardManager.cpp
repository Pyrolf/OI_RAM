#include "KeyboardManager.h"


KeyboardManager::KeyboardManager()
{
	auto eventListener = EventListenerKeyboard::create();

	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
		// If a key already exists, do nothing as it will already have a time stamp
		// Otherwise, set's the timestamp to now
		if (keys.find(keyCode) == keys.end()){
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
		// remove the key.  std::map.erase() doesn't care if the key doesnt exist
		if (keys.find(keyCode) != keys.end())
			keys.erase(keyCode);
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}


KeyboardManager::~KeyboardManager()
{
}

bool KeyboardManager::isKeyPressed(EventKeyboard::KeyCode code) 
{
	// Check if the key is currently pressed by seeing it it's in the std::map keys
	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
	if (keys.find(code) != keys.end())
		return true;
	return false;
}

double KeyboardManager::keyPressedDuration(EventKeyboard::KeyCode code) 
{
	// Return the amount of time that has elapsed between now and when the user
	// first started holding down the key in milliseconds
	// Obviously the start time is the value we hold in our std::map keys
	if (keys.find(code) != keys.end())
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - keys[code]).count();
	else
		return -1;
}

void KeyboardManager::removeKey(EventKeyboard::KeyCode code)
{
	// Check if the key is currently pressed by seeing it it's in the std::map keys
	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
	if (keys.find(code) != keys.end())
	{
		keys.erase(code);
	}
}
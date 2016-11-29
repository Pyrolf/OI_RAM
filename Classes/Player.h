#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Player : public cocos2d::Node
{
public:
	Player();
	~Player();

private:
	Sprite* sprite;
	//Node* playerTop, *playerBottom;
};
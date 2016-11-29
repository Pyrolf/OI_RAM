#include "Player.h"


Player::Player()
{
	sprite = Sprite::create("animations/knight/idle/frame_1.png");
	addChild(sprite);

	auto spriteSize = sprite->getContentSize();

	PhysicsBody* Top;
	Top = PhysicsBody::createBox(Size(spriteSize.width, spriteSize.height));
	//playerTop = Node::create();
	//playerTop->setPhysicsBody(Top);
	setPhysicsBody(Top);

	/*PhysicsBody* Bottom;
	Bottom = PhysicsBody::createBox(Size(spriteSize.width - 2, 20));
	playerBottom = Node::create();
	playerBottom->setPhysicsBody(Bottom);
	addChild(playerBottom);*/

	//PhysicsJointFixed::construct(Top, Bottom, this->getPosition())->setCollisionEnable(false);

	/*auto node = Node::create();
	node->setPosition(p);
	node->setPhysicsBody(body);

	tileCollisionNodes->addChild(node);*/
}


Player::~Player()
{
}

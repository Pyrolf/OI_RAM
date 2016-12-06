#include "Player.h"
#include "CollisionManager.h"


Player::Player()
{
	sprite = Sprite::create("animations/knight/idle/frame_1.png");
	addChild(sprite);

	auto spriteSize = sprite->getContentSize();

	PhysicsBody* Body;
	Body = PhysicsBody::createBox(Size(spriteSize.width, spriteSize.height), PhysicsMaterial(1, 0, 0));
	//Body->addShape(PhysicsShapeBox::create(Size(spriteSize.width - 2, 4), PhysicsMaterial(1, 0, 0), Vec2(0, -spriteSize.height / 2 + 2)));
	Body->setMass(1);
	Body->setRotationEnable(false);

	Body->setCollisionBitmask(CCollisionManager::CB_PLAYER);
	Body->setContactTestBitmask(1);

	setPhysicsBody(Body);
	

	Body = PhysicsBody::createBox(Size(spriteSize.width - 2, 4), PhysicsMaterial(1, 0, 0), Vec2(0, -spriteSize.height / 2 + 2));
	Body->setMass(1);
	Body->setDynamic(false);

	Body->setCollisionBitmask(CCollisionManager::CB_PLAYER_BOTTOM);
	Body->setContactTestBitmask(1);

	auto n = Node::create();
	n->setPhysicsBody(Body);
	addChild(n);

	this->scheduleUpdate();
}

Player::~Player()
{
}

void Player::update(float dt)
{
	auto Body = this->getPhysicsBody();

	if (!isMoving && frictionLerpValue > 0)
	{
		frictionLerpValue -= dt * frictionMulti;
		if (frictionLerpValue < 0)
			frictionLerpValue = 0;

		Vec2 a = Body->getVelocity();

		Body->setVelocity(Vec2(0, Body->getVelocity().y).lerp(Body->getVelocity(), frictionLerpValue));

		a = Body->getVelocity();
	}
	
	isMoving = false;
}

void Player::Move(bool right, float speed, float dt)
{
	isMoving = true;
	frictionLerpValue = 1;

	auto body = this->getPhysicsBody();

	if (right)
		body->applyImpulse(Vec2(body->getMass() * 400.0f  * dt, 0));
	else
		body->applyImpulse(Vec2(body->getMass() * -400.0f  * dt, 0));


	if (body->getVelocity().x > 150)
		body->setVelocity(Vec2(150, body->getVelocity().y));
	else if (body->getVelocity().x < -150)
		body->setVelocity(Vec2(-150, body->getVelocity().y));

	//if (body->)
}

void Player::Jump()
{
	if (jumpCount < maxJumpCount)
	{
		auto body = this->getPhysicsBody();

		body->setVelocity(Vec2(body->getVelocity().x, 0));
		body->applyImpulse(Vec2(0, this->getPhysicsBody()->getMass() * 300));
		jumpCount++;
	}
}
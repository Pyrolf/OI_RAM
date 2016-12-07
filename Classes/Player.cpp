#include "Player.h"
#include "CollisionManager.h"
#include "KeyboardManager.h"

Player::Player()
: CGameObject()
{
}

Player::~Player()
{
}

void Player::Init(Vec2 Pos)
{
	this->setPosition(Pos);

	Sprite* temp = Sprite::create("animations/knight/idle/frame_1.png");
	auto spriteSize = temp->getContentSize();

	this->SetSprite(temp, spriteSize);


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

void Player::update(float dt)
{
	Movement(dt);

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

void Player::Move(bool right, float dt)
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
}

void Player::Jump()
{
	if (jumpCount < maxJumpCount)
	{
		auto body = this->getPhysicsBody();

		body->setVelocity(Vec2(body->getVelocity().x, 0));
		body->applyImpulse(Vec2(0, this->getPhysicsBody()->getMass() * 400));
		jumpCount++;
	}
}

bool upKeypress = false;

void Player::Movement(float dt)
{
	if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_A))
	{
		Move(false, dt);
	}
	if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_D))
	{
		Move(true, dt);
	}
	if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) && !upKeypress)
	{
		upKeypress = true;
		Jump();
	}
	else if (!KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) && upKeypress)
	{
		upKeypress = false;
	}
	/*if (KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || KeyboardManager::GetInstance()->isKeyPressed(EventKeyboard::KeyCode::KEY_S))
	{
		c->setPosition(c->getPositionX(), c->getPositionY() - dt * 500);
	}*/
}
#include "FollowWithLerp.h"


FollowWithLerp::FollowWithLerp()
{
	speed = 3;
}

FollowWithLerp::~FollowWithLerp()
{
}

FollowWithLerp* FollowWithLerp::create(Node *followedNode, float speed, const Rect& rect/* = Rect::ZERO*/)
{
	FollowWithLerp *follow = new (std::nothrow) FollowWithLerp();
	follow->speed = speed;
	if (follow && follow->initWithTarget(followedNode, rect))
	{
		follow->autorelease();
		return follow;
	}
	CC_SAFE_DELETE(follow);
	return nullptr;
}

void FollowWithLerp::setParallaxScrolling(cocos2d::experimental::TMXTiledMap * tilemap)
{
	this->tilemap = tilemap;
}

void FollowWithLerp::step(float dt)
{
	if (_boundarySet)
	{
		// whole map fits inside a single screen, no need to modify the position - unless map boundaries are increased
		if (_boundaryFullyCovered)
		{
			return;
		}

		Vec2 targetPos = (_halfScreenSize - _followedNode->getPosition());

		Vec2 dir = targetPos - _target->getPosition();

		_target->setPosition(clampf(_target->getPosition().x + dir.x * dt * speed, _leftBoundary, _rightBoundary),
			clampf(_target->getPosition().y + dir.y * dt * speed, _bottomBoundary, _topBoundary));

		if (tilemap != nullptr)
			tilemapParallaxScrolling(targetPos, dir, dt);
	}
	else
	{
		Vec2 targetPos = (_halfScreenSize - _followedNode->getPosition());
		
		Vec2 dir = targetPos - _target->getPosition();
		
		_target->setPosition(_target->getPosition() + (dir)* dt * speed);
	}
}

void FollowWithLerp::tilemapParallaxScrolling(Vec2 targetPos, Vec2 dir, float dt)
{
	for (auto& object : tilemap->getChildren())
	{
		auto layer = dynamic_cast<cocos2d::experimental::TMXLayer*>(object);
		if (layer->getLayerName().find("Scrolling") != std::string::npos)
		{/*
			Vec2 akbvr = layer->convertToWorldSpace(layer->getPosition());

			layer->setPosition(clampf(akbvr.x - dir.x * dt * speed, _leftBoundary, _rightBoundary),
				clampf(akbvr.y - dir.y * dt * speed, _bottomBoundary, _topBoundary));*/
		}
	}
}
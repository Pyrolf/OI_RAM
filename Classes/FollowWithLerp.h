#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class FollowWithLerp : public Follow
{
public:
	FollowWithLerp();
	~FollowWithLerp();

	static FollowWithLerp* create(Node *followedNode, float speed = 3, const Rect& rect = Rect::ZERO);

	void setParallaxScrolling(cocos2d::experimental::TMXTiledMap * tilemap);

	virtual void step(float dt) override;

private:
	float speed;

	cocos2d::experimental::TMXTiledMap * tilemap = nullptr;

	void tilemapParallaxScrolling(Vec2 targetPos, Vec2 dir, float dt);
};
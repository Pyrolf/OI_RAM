#pragma once
#include "cocos2d.h"
#include "EffectTileMap.h"

using namespace cocos2d;
using std::string;

class TilemapManager
{
public:
	TilemapManager(string filepath, Layer* theLayer, int Zorder = 0);
	~TilemapManager();
	
	cocos2d::experimental::TMXTiledMap * getTilemap() { return tilemap; };

private:
	void spawnBoundingBoxes(cocos2d::experimental::TMXLayer* layer);

	void createRectangularFixture(cocos2d::experimental::TMXLayer* layer, int x, int y, int offset, bool isHorizontal);

	cocos2d::experimental::TMXTiledMap * tilemap;
	Layer* theLayer;
	
	Node* tileCollisionNodes;
};


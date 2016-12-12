#include "TilemapManager.h"
#include "CollisionManager.h"

const float pixelsPerMeter = 32.0f;
const float Gravity = -pixelsPerMeter / 0.98f;

TilemapManager::TilemapManager(string filepath, Layer* theLayer, int Zorder)
{
	//physicsWorld = new b2World(b2Vec2(0.0f, Gravity));

	//physicsWorld->SetAllowSleeping(true);
	//physicsWorld->SetContinuousPhysics(true);
	///////////////////for colision responce in the future///////////////////////////////
	////physicsWorld->SetContactListener();
	//physicsWorld->DrawDebugData();

	this->theLayer = theLayer;
	

	tileCollisionNodes = Node::create();

	tilemap = cocos2d::experimental::TMXTiledMap::create(filepath);

	if (tilemap)
	{
		for (auto& object : tilemap->getChildren())
		{
			auto layer = dynamic_cast<cocos2d::experimental::TMXLayer*>(object);
			if (layer->getLayerName().find("Collision") != string::npos)
			{
				spawnBoundingBoxes(layer);
				layer->setVisible(false);
			}
		}
	}

	if (Zorder)
		theLayer->addChild(tilemap, Zorder);
	else
		theLayer->addChild(tilemap);

	theLayer->addChild(tileCollisionNodes);
}


TilemapManager::~TilemapManager()
{
}

void TilemapManager::spawnBoundingBoxes(cocos2d::experimental::TMXLayer* layer)
{
	Size layerSize = layer->getLayerSize();
	for (int x = 0; x < layerSize.width; x++)
	{
		int startPos = -1, offset = 0;
		
		for (int y = 0; y < layerSize.height; y++)
		{
			auto tileSprite = layer->getTileAt(Point(x, y));
			if (tileSprite)
			{
				if (startPos < 0)
				{
					if (y + 1 >= layerSize.height || !(layer->getTileAt(Point(x, y + 1))))
						continue;
					startPos = y;
				}
				else
				{
					offset++;
					if (y + 1 == layerSize.height)
						createRectangularFixture(layer, x, startPos, offset, false);
				}
			}
			else
			{
				if (startPos >= 0)
				{
					createRectangularFixture(layer, x, startPos, offset, false);
					startPos = -1;
					offset = 0;
				}
			}
		}
	}
	for (int y = 0; y < layerSize.height; y++)
	{
		int startPos = -1, offset = 0;

			for (int x = 0; x < layerSize.width; x++)
			{
			auto tileSprite = layer->getTileAt(Point(x, y));
			if (tileSprite)
			{
				if (startPos < 0)
				{
					if ((y - 1 >= 0 && (layer->getTileAt(Point(x, y - 1)))) || (y + 1 < layerSize.height && layer->getTileAt(Point(x, y + 1))))
						continue;
					startPos = x;
				}
				else
				{
					if ((y - 1 >= 0 && (layer->getTileAt(Point(x, y - 1)))) || (y + 1 < layerSize.height && layer->getTileAt(Point(x, y + 1))))
					{
						createRectangularFixture(layer, startPos, y, offset, true);
						startPos = -1;
						offset = 0;
						continue;
					}
					offset++;
				}
			}
			else
			{
				if (startPos >= 0)
				{
					createRectangularFixture(layer, startPos, y, offset, true);
					startPos = -1;
					offset = 0;
				}
			}

			if (x + 1 == layerSize.width && startPos >= 0)
				createRectangularFixture(layer, startPos, y, offset, true);
		}
	}
}

void TilemapManager::createRectangularFixture(cocos2d::experimental::TMXLayer* layer, int x, int y, int offset, bool isHorizontal)
{
	Size tileSize = tilemap->getTileSize();

	Vec2 p = layer->getPositionAt(Point(x, y));
	if (isHorizontal)
	{
		p.x += std::abs(layer->getPositionAt(Point(x + offset, y)).x + tileSize.width - p.x) * 0.5;
		p.y += tileSize.height * 0.5;
	}
	else
	{
		p.x += tileSize.width * 0.5;
		p.y -= std::abs(layer->getPositionAt(Point(x, y + offset)).y - p.y) * 0.5 - tileSize.width * 0.5;
	}

	PhysicsBody* body;
	if (isHorizontal)
		body = PhysicsBody::createBox(Size(tileSize.width * (offset + 1), tileSize.height), PhysicsMaterial(1, 1, 1));
	else
		body = PhysicsBody::createBox(Size(tileSize.width, tileSize.height * (offset + 1)), PhysicsMaterial(1, 1, 1));

	body->setDynamic(false);
	body->setCollisionBitmask(CCollisionManager::CB_GROUND);
	body->setContactTestBitmask(1);

	auto node = Node::create();
	node->setName("TileColisionNode");
	node->setPosition(p);
	node->setPhysicsBody(body);

	tileCollisionNodes->addChild(node);
}
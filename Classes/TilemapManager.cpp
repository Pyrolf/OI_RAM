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
		Vector<cocos2d::experimental::TMXLayer*> dubLayers;
		for (auto& object : tilemap->getChildren())
		{
			auto layer = dynamic_cast<cocos2d::experimental::TMXLayer*>(object);
			if (layer->getLayerName().find("Collision") != string::npos)
			{
				spawnBoundingBoxes(layer);
				layer->setVisible(false);
			}

			Value temp = layer->getProperty("x_position");
			if (!temp.isNull())
			{
				float xpos;
				xpos = std::stof(temp.asString());

				layer->setPosition(xpos, layer->getPosition().y);
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


void TilemapManager::SpawnGameObjects(CGameObjectManager* GOM)
{
	auto objectGroups = tilemap->getObjectGroups();
	for (auto& objectGroup : objectGroups)
	{
		auto objects = objectGroup->getObjects();
		for (auto& object : objects)
		{
			auto properties = object.asValueMap();
			auto type = properties.at("type").asString();

			auto x = properties.at("x").asFloat();
			auto y = properties.at("y").asFloat();

			if (type == "Player")
			{
				GOM->SpawnPlayer(Vec2(x, y));
			}
			else if (type == "Enemy_Weak")
			{
				GOM->SpawnEnemy(Vec2(x, y), CEnemy::ENEMY_TYPE_WEAK);
			}
			else if (type == "Enemy_Strong")
			{
				GOM->SpawnEnemy(Vec2(x, y), CEnemy::ENEMY_TYPE_STRONG);
			}
			else if (type == "Enemy_Pouncer")
			{
				GOM->SpawnEnemy(Vec2(x, y), CEnemy::ENEMY_TYPE_POUNCER);
			}
			else if (type == "Enemy_Shooter")
			{
				GOM->SpawnEnemy(Vec2(x, y), CEnemy::ENEMY_TYPE_SHOOTER);
			}
			else if (type == "Enemy_Hybrid")
			{
				GOM->SpawnEnemy(Vec2(x, y), CEnemy::ENEMY_TYPE_HYBRID);
			}
			else if (type == "Coin")
			{
				GOM->SpawnInteractableItem(Vec2(x, y), CInteractableGameObject::COIN);
			}
			else if (type == "Live")
			{
				GOM->SpawnInteractableItem(Vec2(x, y), CInteractableGameObject::LIVE);
			}
			else if (type == "Mana_Potion")
			{
				GOM->SpawnInteractableItem(Vec2(x, y), CInteractableGameObject::MANA_POTION);
			}
			else if (type == "Exit")
			{
				GOM->SpawnInteractableItem(Vec2(x, y), CInteractableGameObject::EXIT);
			}
			else if (type == "Crate")
			{
				GOM->SpawnPhysicsGO(Vec2(x, y), CPhysicsGameObject::CRATE);
			}
			else if (type == "Jumppad")
			{
				GOM->SpawnPhysicsGO(Vec2(x, y), CPhysicsGameObject::JUMPPAD);
			}
		}
	}
}

//m_pGOManager->SpawnPlayer(Vec2(origin.x + visibleSize.width / 2,
//	origin.y + visibleSize.height * 0.75f));
////play particle at the player
////CParticleLoader::createBleedingEffect(m_pGOManager->getPlayer());
//
//// Spawn Enemy
//// Weak
//for (int i = 0; i < 1; i++)
//{
//	Vec2 position(visibleSize.width * 0.15f + origin.x + visibleSize.width * 0.2f * i,
//		visibleSize.height * 0.6f + origin.y);
//	m_pGOManager->SpawnEnemy(position, CEnemy::ENEMY_TYPE_WEAK);
//}
//// Strong
//for (int i = 0; i < 1; i++)
//{
//	Vec2 position(visibleSize.width * 0.7f + origin.x + visibleSize.width * 0.2f * i,
//		visibleSize.height * 0.6f + origin.y);
//	m_pGOManager->SpawnEnemy(position, CEnemy::ENEMY_TYPE_STRONG);
//}
//// Pouncer
//for (int i = 0; i < 1; i++)
//{
//	Vec2 position(visibleSize.width * 1.0f + origin.x + visibleSize.width * 0.2f * i,
//		visibleSize.height * 0.6f + origin.y);
//	m_pGOManager->SpawnEnemy(position, CEnemy::ENEMY_TYPE_POUNCER);
//}
//// Shoot
//for (int i = 0; i < 1; i++)
//{
//	Vec2 position(visibleSize.width * 1.5f + origin.x + visibleSize.width * 0.2f * i,
//		visibleSize.height * 0.6f + origin.y);
//	m_pGOManager->SpawnEnemy(position, CEnemy::ENEMY_TYPE_SHOOTER);
//}
//// Hybrid
//for (int i = 0; i < 1; i++)
//{
//	Vec2 position(visibleSize.width * 2.0f + origin.x + visibleSize.width * 0.2f * i,
//		visibleSize.height * 0.6f + origin.y);
//	m_pGOManager->SpawnEnemy(position, CEnemy::ENEMY_TYPE_HYBRID);
//}
//
//// Spawn Items
//for (int i = 0; i < 1; i++)
//{
//	Vec2 position(visibleSize.width * 0.3f + origin.x + visibleSize.width * 0.2f * i,
//		visibleSize.height * 0.6f + origin.y);
//	m_pGOManager->SpawnPhysicsGO(position, CPhysicsGameObject::JUMPPAD);
//}
//for (int i = 0; i < 1; i++)
//{
//	Vec2 position(visibleSize.width * 0.7f + origin.x + visibleSize.width * 0.2f * i,
//		visibleSize.height * 0.6f + origin.y);
//	m_pGOManager->SpawnInteractableItem(position, CInteractableGameObject::LIVE);
//}
//for (int i = 0; i < 1; i++)
//{
//	Vec2 position(visibleSize.width * 1.0f + origin.x + visibleSize.width * 0.2f * i,
//		visibleSize.height * 0.6f + origin.y);
//	m_pGOManager->SpawnInteractableItem(position, CInteractableGameObject::MANA_POTION);
//}
#include "SpriteLoader.h"
#include "SpriteSystem.h"

USING_NS_CC;

void CSpriteLoader::loadEnemySprites(CEnemy::ENEMY_TYPE type, Size size)
{
	switch (type)
	{
		case CEnemy::ENEMY_TYPE_POUNCER:
		{
			CSpriteSystem::getInstance()->getSprite("animations/monsters/monster1/idle/frame_1.png", size);
			break;
		}
		default:
		{
			CSpriteSystem::getInstance()->getSprite("animations/monsters/monster1/idle/frame_1.png", size);
			break;
		}
	}
}

Sprite* CSpriteLoader::getEnemySprite(CEnemy::ENEMY_TYPE type, Size size)
{
	switch (type)
	{
		case CEnemy::ENEMY_TYPE_POUNCER:
		{
			return CSpriteSystem::getInstance()->getSprite("animations/monsters/monster1/idle/frame_1.png", size);
			break;
		}
		default:
		{
			return CSpriteSystem::getInstance()->getSprite("animations/monsters/monster1/idle/frame_1.png", size);
			break;
		}
	}
}

void CSpriteLoader::loadProjectileSprites(cocos2d::Size size)
{
	CSpriteSystem::getInstance()->getSprite("animations/monsters/monster1/idle/frame_1.png", size);
}

Sprite* CSpriteLoader::getProjectileSprites(Size size)
{
	return CSpriteSystem::getInstance()->getSprite("animations/monsters/monster1/idle/frame_1.png", size);
}

void CSpriteLoader::loadInteractiveItemSprites(CInteractableGameObject::TYPE type, cocos2d::Size size)
{
	switch (type)
	{
		case CInteractableGameObject::COIN:
		{
			CSpriteSystem::getInstance()->getSprite("images/coin.png", size);
			break;
		}
		case CInteractableGameObject::LIVE:
		{
			CSpriteSystem::getInstance()->getSprite("images/heart.png", size);
			break;
		}
		case CInteractableGameObject::MANA_POTION:
		{
			CSpriteSystem::getInstance()->getSprite("images/mana_potion.png", size);
			break;
		}
		default:
		{
			CSpriteSystem::getInstance()->getSprite("images/coin.png", size);
			break;
		}
	}
}

Sprite* CSpriteLoader::getInteractiveItemSprites(CInteractableGameObject::TYPE type, cocos2d::Size size)
{
	switch (type)
	{
		case CInteractableGameObject::COIN:
		{
			return CSpriteSystem::getInstance()->getSprite("images/coin.png", size);
			break;
		}
		case CInteractableGameObject::LIVE:
		{
			return CSpriteSystem::getInstance()->getSprite("images/heart.png", size);
			break;
		}
		case CInteractableGameObject::MANA_POTION:
		{
			return CSpriteSystem::getInstance()->getSprite("images/mana_potion.png", size);
			break;
		}
		default:
		{
			return CSpriteSystem::getInstance()->getSprite("images/coin.png", size);
			break;
		}
	}
}

void CSpriteLoader::loadPlayerSprites(cocos2d::Size size)
{
	CSpriteSystem::getInstance()->getSprite("animations/knight/idle/frame_1.png", size);
}

Sprite* CSpriteLoader::getPlayerSprite(Size size)
{
	return CSpriteSystem::getInstance()->getSprite("animations/knight/idle/frame_1.png", size);
}
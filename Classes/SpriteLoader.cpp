#include "SpriteLoader.h"
#include "SpriteSystem.h"

USING_NS_CC;

void CSpriteLoader::loadEnemiesSprites(cocos2d::Size size)
{
	CSpriteSystem::getInstance()->getSprite("animations/monsters/monster1/idle/frame_1.png", size);
}

Sprite* CSpriteLoader::getEnemySprite(Size size)
{
	return CSpriteSystem::getInstance()->getSprite("animations/monsters/monster1/idle/frame_1.png", size);
}

//Sprite* CSpriteLoader::getPlayerSprite()
//{
//	return CSpriteSystem::getInstance()->getSprite("animations/knight/idle/frame_1.png", size);
//}
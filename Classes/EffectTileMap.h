#pragma once
#include "cocos2d.h"
#include "EffectTileLayer.h"

using namespace cocos2d;

class EffectTileMap : public experimental::TMXTiledMap
{
public:
	EffectTileMap();
	~EffectTileMap();

	static EffectTileMap * create(const std::string& tmxFile);

	bool initWithTMXFile(const std::string& tmxFile);
	
protected:
	void buildWithMapInfo(TMXMapInfo* mapInfo);

	EffectTileLayer * parseLayer(TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
};


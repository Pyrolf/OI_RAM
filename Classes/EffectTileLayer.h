#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class EffectTileLayer : public experimental::TMXLayer
{
public:
	EffectTileLayer();
	~EffectTileLayer();

	static EffectTileLayer * create(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);

	//void setEffect(LightEffect *effect);

	void setLayerNormalmap();

	Texture2D * getLayerNormalMap() { return _LayerNormalmap; };
protected:
	bool initWithTilesetInfo(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

private:
	//LightEffect *_effect = nullptr;
	Texture2D *_normalmap = nullptr;
	Texture2D *_LayerNormalmap = nullptr;

	Sprite* Sp = nullptr;
	Node* tempNode = nullptr;
};


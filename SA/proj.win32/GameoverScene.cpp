#include "GameoverScene.h"
#include "GameoverLayer.h"

USING_NS_CC;

CCScene* GameoverScene::scene()
{
	CCScene *scene = GameoverScene::create();

	return scene;
}

bool GameoverScene::init()
{
	GameoverLayer *layer = GameoverLayer::create() ;

	this->addChild(layer) ;
    
	return true;
}
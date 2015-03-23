#include "GameScene.h"
#include "GameLayer.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
	CCScene *scene = GameScene::create();

	return scene;
}

bool GameScene::init()
{
	GameLayer *layer = GameLayer::create() ;

	this->addChild(layer) ;
    
	return true;
}
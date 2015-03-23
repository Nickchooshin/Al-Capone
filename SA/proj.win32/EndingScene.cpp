#include "EndingScene.h"
#include "EndingLayer.h"

USING_NS_CC;

CCScene* EndingScene::scene()
{
	CCScene *scene = EndingScene::create();

	return scene;
}

bool EndingScene::init()
{
	EndingLayer *layer = EndingLayer::create() ;

	this->addChild(layer) ;
    
	return true;
}
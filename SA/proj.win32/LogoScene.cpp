#include "LogoScene.h"
#include "LogoLayer.h"

USING_NS_CC;

CCScene* LogoScene::scene()
{
	CCScene *scene = LogoScene::create();

	return scene;
}

bool LogoScene::init()
{
	LogoLayer *layer = LogoLayer::create() ;

	this->addChild(layer) ;
    
	return true;
}
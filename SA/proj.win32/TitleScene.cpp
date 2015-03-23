#include "TitleScene.h"
#include "TitleLayer.h"

USING_NS_CC;

CCScene* TitleScene::scene()
{
	CCScene *scene = TitleScene::create();

	return scene;
}

bool TitleScene::init()
{
	TitleLayer *layer = TitleLayer::create() ;

	this->addChild(layer) ;
    
	return true;
}
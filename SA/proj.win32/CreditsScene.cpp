#include "CreditsScene.h"
#include "CreditsLayer.h"

USING_NS_CC;

CCScene* CreditsScene::scene()
{
	CCScene *scene = CreditsScene::create();

	return scene;
}

bool CreditsScene::init()
{
	CreditsLayer *layer = CreditsLayer::create() ;

	this->addChild(layer) ;
    
	return true;
}
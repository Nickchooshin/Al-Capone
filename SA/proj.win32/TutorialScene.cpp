#include "TutorialScene.h"
#include "TutorialLayer.h"

USING_NS_CC;

CCScene* TutorialScene::scene()
{
	CCScene *scene = TutorialScene::create();

	return scene;
}

bool TutorialScene::init()
{
	TutorialLayer *layer = TutorialLayer::create() ;

	this->addChild(layer) ;
    
	return true;
}
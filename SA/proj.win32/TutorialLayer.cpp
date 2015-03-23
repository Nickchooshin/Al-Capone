#include "TutorialLayer.h"

#include "GameScene.h"

USING_NS_CC;

bool TutorialLayer::init()
{
	if ( !CCLayer::init() )
    {
		return false;
	}

	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true) ;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize() ;

	CCSprite *pTutorialImage = CCSprite::create("Image/Tutorial/Tutorial_Image.png") ;
	pTutorialImage->setPosition(ccp(visibleSize.width/2, visibleSize.height/2)) ;
	this->addChild(pTutorialImage, 0) ;
    
	return true;
}

void TutorialLayer::update(float dt)
{
}

bool TutorialLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true ;
}

void TutorialLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void TutorialLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->replaceScene(GameScene::scene()) ;
}

void TutorialLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}
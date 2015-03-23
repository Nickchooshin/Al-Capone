#include "EndingLayer.h"

#include "TitleScene.h"

USING_NS_CC;

bool EndingLayer::init()
{
	if ( !CCLayer::init() )
    {
		return false;
	}

	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true) ;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize() ;

	CCSprite *pEnding = CCSprite::create("Image/Game/End/Ending.png") ;
	pEnding->setPosition(ccp(visibleSize.width/2, visibleSize.height/2)) ;
	this->addChild(pEnding, 0) ;
    
	return true;
}

void EndingLayer::update(float dt)
{
}

bool EndingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->replaceScene(TitleScene::scene()) ;

	return true ;
}

void EndingLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void EndingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void EndingLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}
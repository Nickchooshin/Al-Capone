#include "CreditsLayer.h"

#include "TitleScene.h"

USING_NS_CC;

bool CreditsLayer::init()
{
	if ( !CCLayer::init() )
    {
		return false;
	}

	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true) ;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize() ;
    
	return true;
}

void CreditsLayer::update(float dt)
{
}

bool CreditsLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->replaceScene(TitleScene::scene()) ;

	return true ;
}

void CreditsLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CreditsLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CreditsLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}
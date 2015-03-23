#include "GameoverLayer.h"

#include "TitleScene.h"

USING_NS_CC;

bool GameoverLayer::init()
{
	if ( !CCLayer::init() )
    {
		return false;
	}

	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true) ;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize() ;

	CCSprite *pEnding = CCSprite::create("Image/Game/End/Gameover.png") ;
	pEnding->setPosition(ccp(visibleSize.width/2, visibleSize.height/2)) ;
	this->addChild(pEnding, 0) ;
    
	return true;
}

void GameoverLayer::update(float dt)
{
}

bool GameoverLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->replaceScene(TitleScene::scene()) ;

	return true ;
}

void GameoverLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void GameoverLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void GameoverLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}
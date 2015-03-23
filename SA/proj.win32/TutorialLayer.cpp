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

	m_nPage = 0 ;

	for(int i=0; i<2; i++)
	{
		char str[1024] ; 
		sprintf(str, "Image/Tutorial/Tutorial_Image%d.png", i+1) ;
		m_pTutorialImage[i] = CCSprite::create(str) ;
		m_pTutorialImage[i]->setPosition(ccp(visibleSize.width/2, visibleSize.height/2)) ;
		this->addChild(m_pTutorialImage[i], 0) ;
	}

	m_pTutorialImage[0]->setVisible(true) ;
	m_pTutorialImage[1]->setVisible(false) ;
    
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
	m_pTutorialImage[m_nPage]->setVisible(false) ;
	m_nPage += 1 ;

	if(m_nPage>=2)
	{
		CCDirector *pDirector = CCDirector::sharedDirector() ;
		pDirector->replaceScene(GameScene::scene()) ;
	}
	else
	{
		m_pTutorialImage[m_nPage]->setVisible(true) ;
	}
}

void TutorialLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}
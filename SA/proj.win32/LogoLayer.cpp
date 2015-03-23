#include "LogoLayer.h"

#include "TitleScene.h"

USING_NS_CC;

bool LogoLayer::init()
{
	if ( !CCLayer::init() )
    {
		return false;
	}

	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true) ;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize() ;

	m_bCreator = true ;
	m_nLogoState = 0 ;

	m_pCreator = CCSprite::create("Image/Logo/Team_Creator.png") ;
	m_pCreator->setPosition(ccp(visibleSize.width/2, visibleSize.height/2)) ;
	m_pCreator->setOpacity(0) ;
	this->addChild(m_pCreator, 0) ;

	m_pTeamLogo = CCSprite::create("Image/Logo/Team_Logo.png") ;
	m_pTeamLogo->setPosition(ccp(visibleSize.width/2, visibleSize.height/2)) ;
	m_pTeamLogo->setOpacity(0) ;
	this->addChild(m_pTeamLogo, 0) ;

	scheduleUpdate() ;
    
	return true;
}

void LogoLayer::update(float dt)
{
	static float time=0.0f ;
	int nOpacity ;
	CCSprite *pLogo ;

	time += dt ;
	nOpacity = 255 * (time/1.0f) ;
	if(nOpacity>255)
		nOpacity = 255 ;

	if(m_bCreator)
		pLogo = m_pCreator ;
	else
		pLogo = m_pTeamLogo ;

	if(m_nLogoState==0)
		pLogo->setOpacity( nOpacity ) ;
	else if(m_nLogoState==1)
		pLogo->setOpacity( 255 ) ;
	else if(m_nLogoState==2)
		pLogo->setOpacity( 255 - nOpacity ) ;

	if(time>=1.0f)
	{
		time = 0.0f ;
		++m_nLogoState ;

		if(m_nLogoState==3)
		{
			if(m_bCreator)
			{
				m_bCreator = false ;
			}
			else
			{
				CCDirector *pDirector = CCDirector::sharedDirector() ;
				pDirector->replaceScene(TitleScene::scene()) ;
			}

			pLogo->setVisible(false) ;
			m_nLogoState = 0 ;
		}
	}
}

bool LogoLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true ;
}

void LogoLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void LogoLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->replaceScene(TitleScene::scene()) ;
}

void LogoLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}
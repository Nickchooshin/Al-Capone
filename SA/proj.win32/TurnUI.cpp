#include "TurnUI.h"
#include "Data.h"

#include "Manager.h"

#include "SimpleAudioEngine.h"

bool CTurnUI::init()
{
	CCMenuItemImage *pTurnMenu = CCMenuItemImage::create("Image/Game/UI/Play_1.png", "Image/Game/UI/Play_2.png", this, menu_selector(CTurnUI::TurnFlow)) ;
	pTurnMenu->setAnchorPoint(ccp(0, 0.5)) ;
	pTurnMenu->setPosition(ccp( 0, 0 )) ;
	CCMenu *pMenu = CCMenu::create(pTurnMenu, NULL) ;
	pMenu->setPosition(ccp( 0, 0 )) ;
	this->addChild(pMenu, 0) ;

	CCSprite *pTurnSprite = CCSprite::create("Image/Game/UI/Turn.png") ;
	pTurnSprite->setAnchorPoint(ccp(0, 0.5)) ;
	pTurnSprite->setPosition(ccp( pTurnMenu->getPosition().x + pTurnMenu->getContentSize().width + 10,
									0 )) ;
	this->addChild(pTurnSprite, 0) ;

	CCSprite *pRoundSprite = CCSprite::create("Image/Game/UI/Round.png") ;
	pRoundSprite->setAnchorPoint(ccp(0, 0.5)) ;
	pRoundSprite->setPosition(ccp( pTurnSprite->getPosition().x + pTurnSprite->getContentSize().width + 10,
									0)) ;
	this->addChild(pRoundSprite, 0) ;

	char str[12] ;

	sprintf(str, "%d", g_pData->m_User.m_Turn.GetTurn()) ;
	pTurnLabel = CCLabelTTF::create(str, "fonts/arial.ttf", 30, pTurnSprite->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
	pTurnLabel->setAnchorPoint(ccp(0, 0.5)) ;
	pTurnLabel->setColor(ccc3(0, 0, 0)) ;
	pTurnLabel->setPosition(pTurnSprite->getPosition()) ;
	this->addChild(pTurnLabel, 1) ;

	sprintf(str, "%d", g_pData->m_User.m_Turn.GetRound()) ;
	pRoundLabel = CCLabelTTF::create(str, "fonts/arial.ttf", 30, pRoundSprite->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
	pRoundLabel->setAnchorPoint(ccp(0, 0.5)) ;
	pRoundLabel->setColor(ccc3(0, 0, 0)) ;
	pRoundLabel->setPosition(pRoundSprite->getPosition()) ;
	this->addChild(pRoundLabel, 1) ;

	return true ;
}

void CTurnUI::TurnFlow(CCObject *pSender)
{
	if(!CManager::Area->isMovingMember())
	{
		g_pData->m_User.m_Turn.TurnFlow() ;

		char str[12] ;

		sprintf(str, "%d", g_pData->m_User.m_Turn.GetTurn()) ;
		pTurnLabel->setString(str) ;

		sprintf(str, "%d", g_pData->m_User.m_Turn.GetRound()) ;
		pRoundLabel->setString(str) ;

		if(g_pData->m_User.m_Turn.GetTurn()!=0)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Turn.wav") ;
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Round.wav") ;
		}
	}
}
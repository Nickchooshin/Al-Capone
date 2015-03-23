#include "MoneyUI.h"

#include "Data.h"

bool CMoneyUI::init()
{
	CCSprite *pFrame = CCSprite::create("Image/Game/UI/Space.png") ;
	pFrame->setPosition(ccp(530, 40)) ;
	this->addChild(pFrame, 0) ;

	CCSprite *pIcon = CCSprite::create("Image/Game/UI/Icon_3.png") ;
	pIcon->setPosition(ccp(460, 40)) ;
	this->addChild(pIcon, 0) ;

	m_pMoneyLabel = CCLabelTTF::create("", "fonts/arial.ttf", 30, CCSize(135, 50), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter) ;
	m_pMoneyLabel->setColor(ccc3(0, 0, 0)) ;
	m_pMoneyLabel->setPosition(ccp(557.5, 40)) ;
	this->addChild(m_pMoneyLabel, 1) ;

	scheduleUpdate() ;

	return true ;
}

void CMoneyUI::update(float dt)
{
	char str[12] ;

	sprintf(str, "%d", g_pData->m_User.m_nMoney) ;
	m_pMoneyLabel->setString(str) ;
}
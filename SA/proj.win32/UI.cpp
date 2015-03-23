#include "UI.h"
#include "TurnUI.h"
#include "MemberUI.h"
#include "MoneyUI.h"
#include "InspectionCheckUI.h"

bool CUI::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite *pUI_1 = CCSprite::create("Image/UI/Background.png") ;
	pUI_1->setPosition(ccp(visibleSize.width/2, 40)) ;
	this->addChild(pUI_1, 0) ;

	CTurnUI *pTurnUI = CTurnUI::create() ;
	pTurnUI->setPosition(ccp(890, 40)) ;
	this->addChild(pTurnUI, 1) ;

	CMemberUI *pMemberUI = CMemberUI::create() ;
	pMemberUI->setPosition(ccp(0, 0)) ;
	this->addChild(pMemberUI, 1) ;

	CMoneyUI *pMoneyUI = CMoneyUI::create() ;
	pMoneyUI->setPosition(ccp(0, 0)) ;
	this->addChild(pMoneyUI) ;

	CInspectionCheckUI *pInspectionCheckUI = CInspectionCheckUI::create() ;
	pInspectionCheckUI->setPosition(ccp(0, 0)) ;
	this->addChild(pInspectionCheckUI) ;

	return true ;
}
#include "Area.h"
#include "Building.h"

#include "BusinessBuilding.h"
#include "ResidentialBuilding.h"

#include "Data.h"

bool CArea::m_bInspectionView[8] ;

bool CArea::init()
{
	int i ;

	m_nAttention = 0 ;
	m_nBaseInspection = 0 ;
	for(i=1; i<=7; i++)
		m_bInspection[i] = false ;

	CCSprite *pSprite ;/*****아마 수정? 해야할듯*****/
	switch(rand()%7)
	{
	case 0 :
		pSprite = CCSprite::create("Image/Area/Building_city_1.png") ;
		break ;
	case 1 :
		pSprite = CCSprite::create("Image/Area/Eco_City_1.png") ;
		break ;
	case 2 :
		pSprite = CCSprite::create("Image/Area/Eco_City_2.png") ;
		break ;
	case 3 :
		pSprite = CCSprite::create("Image/Area/House_City_1.png") ;
		break ;
	case 4 :
		pSprite = CCSprite::create("Image/Area/House_City_2.png") ;
		break ;
	case 5 :
		pSprite = CCSprite::create("Image/Area/Industry_City_1.png") ;
		break ;
	case 6 :
		pSprite = CCSprite::create("Image/Area/Industry_City_2.png") ;
		break ;
	}
	this->addChild(pSprite, 0) ;/*****아마 수정? 해야할듯*****/

	// 봉쇄 이미지
	m_pBlockade = CCSprite::create("Image/Temp/temp_blockade.png") ;
	m_pBlockade->setVisible(false) ;
	this->addChild(m_pBlockade, 2) ;

	// 턴 아이콘
	CCSprite *pTurnMark[7] ;/////***/////
	m_pTurnMark = CCNode::create() ;
	for(i=0; i<7; i++)
	{
		if(i>0)
			pTurnMark[i] = CCSprite::create("Image/Temp/temp_turn_mark2.png") ;
		else
			pTurnMark[i] = CCSprite::create("Image/Temp/temp_turn_mark1.png") ;

		pTurnMark[i]->setTag(i+1) ;
		m_pTurnMark->addChild(pTurnMark[i]) ;
	}

	pTurnMark[3]->setPosition(ccp( pSprite->getPosition().x, pSprite->getPosition().y - 30 )) ;
	for(i=1; i<=3; i++)
	{
		pTurnMark[3-i]->setPosition(ccp( pTurnMark[3-(i-1)]->getPosition().x - (pTurnMark[3-(i-1)]->getContentSize().width - 1),
										 pTurnMark[3-(i-1)]->getPosition().y )) ;
		pTurnMark[3+i]->setPosition(ccp( pTurnMark[3+(i-1)]->getPosition().x + (pTurnMark[3+(i-1)]->getContentSize().width - 1),
										 pTurnMark[3+(i-1)]->getPosition().y )) ;
	}
	m_pTurnMark->setVisible(false) ;
	this->addChild(m_pTurnMark, 2) ;/////***/////

	// 빌딩
	m_pBuilding[0] = CBusinessBuilding::create() ;
	m_pBuilding[1] = CResidentialBuilding::create() ;
	m_pBuilding[0]->setPosition(ccp( pSprite->getPosition().x + pSprite->getContentSize().width/2 - m_pBuilding[0]->getIconSize().width/2,
									 pSprite->getPosition().y + pSprite->getContentSize().height/2 - m_pBuilding[0]->getIconSize().height/2 )) ;
	m_pBuilding[1]->setPosition(ccp( m_pBuilding[0]->getPosition().x - m_pBuilding[0]->getIconSize().width,
									 m_pBuilding[0]->getPositionY() )) ;
	m_pBuilding[0]->setVisible(false) ;
	m_pBuilding[1]->setVisible(false) ;
	this->addChild(m_pBuilding[0], 1) ;
	this->addChild(m_pBuilding[1], 1) ;

	scheduleUpdate() ;

	return true ;
}

void CArea::update(float dt)
{
	int i ;/////***/////
	bool bView=false ;

	if(m_bInspectionView[m_nBaseInspection])
		bView = true ;
	for(i=1; !bView && i<8; i++)
	{
		if(m_bInspection[i] && m_bInspectionView[i])
			bView = true ;
	}

	if(bView)
	{
		m_pTurnMark->setVisible(true) ;

		CCSprite *pTurnMark = (CCSprite*)m_pTurnMark->getChildByTag(m_nBaseInspection) ;
		pTurnMark->setColor(ccc3(255, 0, 0)) ;
		for(i=1; i<8; i++)
		{
			if(m_bInspection[i])
			{
				pTurnMark = (CCSprite*)m_pTurnMark->getChildByTag(i) ;
				pTurnMark->setColor(ccc3(255, 0, 0)) ;
			}
		}
	}
	else
	{
		m_pTurnMark->setVisible(false) ;

		CCSprite *pTurnMark ;
		for(i=1; i<8; i++)
		{
			if(m_bInspection[i])
			{
				pTurnMark = (CCSprite*)m_pTurnMark->getChildByTag(i) ;
				pTurnMark->setColor(ccc3(255, 255, 255)) ;
			}
		}
	}/////***/////
}

void CArea::SetBaseInspection(int turn)
{
	m_nBaseInspection = turn ;
}

void CArea::SetInspection(int turn)
{
	m_bInspection[turn] = true ;
}

void CArea::TurnFlow()
{
	int i ;
	int turn = g_pData->m_User.m_Turn.GetTurn() ;

	if(m_nBaseInspection==turn || m_bInspection[turn])
	{
		for(i=0; i<2; i++)
			m_pBuilding[i]->setEnabled(false) ;
		m_pBlockade->setVisible(true) ;

		CBusinessBuilding *pBusiness = (CBusinessBuilding*)m_pBuilding[0] ;
		pBusiness->Inspection() ;
	}
	else
	{
		for(i=0; i<2; i++)
			m_pBuilding[i]->setEnabled(true) ;
		m_pBlockade->setVisible(false) ;
	}
	
	for(i=0; i<2; i++)
		m_pBuilding[i]->TurnFlow() ;
}

void CArea::RoundFlow()
{
	int i ;

	for(i=0; i<2; i++)
		m_pBuilding[i]->RoundFlow() ;

	if(m_nAttention>0)
		m_nAttention -= 1 ;
}

void CArea::AreaLinked()
{
	m_pBuilding[0]->setVisible(true) ;
	m_pBuilding[1]->setVisible(true) ;
}

bool CArea::GetOwnResidential()
{
	return m_pBuilding[1]->getOwnership() ;
}
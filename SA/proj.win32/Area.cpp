#include "Area.h"
#include "Building.h"
#include "MemberIcon.h"

#include "BusinessBuilding.h"
#include "ResidentialBuilding.h"

#include "Data.h"

#include "SimpleAudioEngine.h"

bool CArea::m_bInspectionView[8] ;

bool CArea::init(int Inspection)
{
	int i ;

	m_bSmuggling = false ;
	m_nAttention = 0 ;
	m_nBaseInspection = 0 ;
	for(i=1; i<=7; i++)
		m_bInspection[i] = false ;
	m_bBlockade = false ;

	m_nBaseInspection = Inspection ;//

	CCSprite *pSprite ;
	switch(m_nBaseInspection)
	{
	case 2 :
		pSprite = CCSprite::create("Image/Game/Area/Eco_City_2.png") ;
		break ;
	case 3 :
		pSprite = CCSprite::create("Image/Game/Area/House_City_1.png") ;
		break ;
	case 4 :
		pSprite = CCSprite::create("Image/Game/Area/House_City_2.png") ;
		break ;
	case 5 :
		pSprite = CCSprite::create("Image/Game/Area/Industry_City_1.png") ;
		break ;
	case 6 :
		pSprite = CCSprite::create("Image/Game/Area/Industry_City_2.png") ;
		break ;
	case 7 :
		pSprite = CCSprite::create("Image/Game/Area/Building_city_1.png") ;
		break ;
	}
	this->addChild(pSprite, 0) ;

	// 봉쇄 이미지
	m_pBlockade[0] = CCSprite::create("Image/Game/Area/Check_Icon.png") ;
	m_pBlockade[1] = CCSprite::create("Image/Game/Area/Lock_Icon.png") ;
	for(i=0; i<2; i++)
	{
		m_pBlockade[i]->setVisible(false) ;
		this->addChild(m_pBlockade[i], 3) ;
	}

	// 턴 아이콘
	CCSprite *pTurnMark[7] ;
	m_pTurnMark = CCNode::create() ;
	for(i=0; i<7; i++)
	{
		char str[1024] ;
		sprintf(str, "Image/Game/UI/InspectionCheck/Day_%d.png", i+1) ;

		pTurnMark[i] = CCSprite::create(str) ;
		pTurnMark[i]->setTag(i+1) ;
		m_pTurnMark->addChild(pTurnMark[i]) ;
	}

	/*pTurnMark[3]->setPosition(ccp( pSprite->getPosition().x, pSprite->getPosition().y - 30 )) ;
	for(i=1; i<=3; i++)
	{
		pTurnMark[3-i]->setPosition(ccp( pTurnMark[3-(i-1)]->getPosition().x - (pTurnMark[3-(i-1)]->getContentSize().width - 1),
										 pTurnMark[3-(i-1)]->getPosition().y )) ;
		pTurnMark[3+i]->setPosition(ccp( pTurnMark[3+(i-1)]->getPosition().x + (pTurnMark[3+(i-1)]->getContentSize().width - 1),
										 pTurnMark[3+(i-1)]->getPosition().y )) ;
	}*/
	pTurnMark[0]->setPosition(ccp( -88, -36 )) ;
	pTurnMark[1]->setPosition(ccp( -65, -36 )) ;
	pTurnMark[2]->setPosition(ccp( -42, -36 )) ;
	pTurnMark[3]->setPosition(ccp( -19, -36 )) ;
	pTurnMark[4]->setPosition(ccp( 4, -36 )) ;
	pTurnMark[5]->setPosition(ccp( 27, -36 )) ;
	pTurnMark[6]->setPosition(ccp( 50, -36 )) ;

	m_pTurnMark->setVisible(false) ;
	this->addChild(m_pTurnMark, 2) ;/////***/////

	// 주목도 수치 표시
	m_pAttentionSprite = CCSprite::create("Image/Game/UI/InspectionCheck/Attention_Frame.png") ;
	m_pAttentionSprite->setPosition(ccp( -83, 0 )) ;
	m_pAttentionSprite->setVisible(false) ;
	this->addChild(m_pAttentionSprite, 2) ;

	m_pAttentionLabel = CCLabelTTF::create("", "fonts/arial.ttf", 27, m_pAttentionSprite->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
	m_pAttentionLabel->setColor(ccc3(0, 0, 0)) ;
	m_pAttentionLabel->setPosition(m_pAttentionSprite->getPosition()) ;
	this->addChild(m_pAttentionLabel, 2) ;

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

	// 멤버 아이콘
	m_pMemberIcon = CMemberIcon::create() ;
	this->addChild(m_pMemberIcon, 2) ;

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

	m_pTurnMark->setVisible(bView) ;
	m_pAttentionSprite->setVisible(bView) ;
	m_pAttentionLabel->setVisible(bView) ;

	if(bView)
	{
		CCSprite *pTurnMark ;

		if(!m_bBlockade)
		{
			for(i=1; i<8; i++)
			{
				pTurnMark = (CCSprite*)m_pTurnMark->getChildByTag(i) ;

				if(m_bInspection[i] || i==m_nBaseInspection)
					pTurnMark->setColor(ccc3(255, 0, 0)) ;
				else if(i!=m_nBaseInspection)
					pTurnMark->setColor(ccc3(255, 255, 255)) ;
			}
		}
		else
		{
			for(i=1; i<8; i++)
			{
				pTurnMark = (CCSprite*)m_pTurnMark->getChildByTag(i) ;
				pTurnMark->setColor(ccc3(255, 0, 0)) ;
			}
		}

		//

		char str[100] ;
		sprintf(str, "%d", m_nAttention) ;

		m_pAttentionLabel->setString(str) ;
	}
}

void CArea::SetSmuggling(bool bSmuggling)
{
	m_bSmuggling = bSmuggling ;
}

/*void CArea::SetBaseInspection(int turn)
{
	m_nBaseInspection = turn ;
}*/

/*void CArea::SetInspection(int turn)
{
	m_bInspection[turn] = true ;
}*/

void CArea::setEnabled(bool bEnabled)
{
	for(int i=0; i<2; i++)
		m_pBuilding[i]->setEnabled(bEnabled) ;
	m_pMemberIcon->setEnabled(bEnabled) ;
}

void CArea::SetAreaBlockade(bool bEnabled)
{
	setEnabled(!bEnabled) ;

	if(!m_bBlockade)
		m_pBlockade[0]->setVisible(bEnabled) ;
	else
		m_pBlockade[1]->setVisible(bEnabled) ;

	if(bEnabled)
	{
		CBusinessBuilding *pBusiness = (CBusinessBuilding*)m_pBuilding[0] ;
		pBusiness->Inspection() ;
		
		m_pMemberIcon->Inspection() ;
	}
}

void CArea::AddAttention(int nAttention)
{
	m_nAttention += nAttention ;

	if(m_nAttention>=12)
	{
		m_nAttention = 12 ;

		m_bBlockade = true ;
		SetAreaBlockade(true) ;

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Block.wav") ;
	}
}

void CArea::TurnFlow()
{
	int i ;
	int turn = g_pData->m_User.m_Turn.GetTurn() ;

	if(!m_bBlockade)
	{
		if(m_nBaseInspection==turn || m_bInspection[turn])
			SetAreaBlockade(true) ;
		else
			SetAreaBlockade(false) ;
	}
	
	for(i=0; i<2; i++)
		m_pBuilding[i]->TurnFlow() ;

	m_pMemberIcon->TurnFlow() ;
}

void CArea::RoundFlow()
{
	int i ;

	for(i=0; i<2; i++)
		m_pBuilding[i]->RoundFlow() ;

	if(m_nAttention>0)
	{
		m_nAttention -= 1 ;

		if(m_nAttention==0)
		{
			SetAreaBlockade(false) ;
			m_bBlockade = false ;
		}
	}

	for(i=1; i<8; i++)
		m_bInspection[i] = false ;

	if(!m_bBlockade && m_nAttention>=2) //
	{
		int r ;
		int n = m_nAttention / 2 ;
		bool aryCheck[8] = {false,} ;

		if(n>5)
			n = 5 ;

		for(i=0; i<n; i++)
		{
			r = rand()%6+2 ;

			if(!aryCheck[r] && r!=m_nBaseInspection)
				m_bInspection[r] = aryCheck[r] = true ;
			else
				--i ;
		}
	}
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

bool CArea::GetOwnBusiness()
{
	return m_pBuilding[0]->getOwnership() ;
}

bool CArea::isSmuggling()
{
	return m_bSmuggling ;
}

bool CArea::isInspection()
{
	return (m_pBlockade[0]->isVisible() || m_pBlockade[1]->isVisible()) ;
}
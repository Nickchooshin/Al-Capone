#include "MemberControlPopup.h"

#include "MemberManager.h"
#include "MemberIcon.h"
#include "AreaManager.h"

CMemberControlPopup::CMemberControlPopup()
{
}

CMemberControlPopup* CMemberControlPopup::GetInstance()
{
	static CMemberControlPopup MemberControlPopup ;

	return &MemberControlPopup ;
}

bool CMemberControlPopup::init()
{
	int i, j ;

	m_pMemberIcon = NULL ;
	m_nTargetIndex = -1 ;

	// 백그라운드
	CCMenuItemImage *pBackgroundItem = CCMenuItemImage::create("Image/Member/Background.png", "Image/Member/Background.png") ;
	pBackgroundItem->setPosition(ccp(640, 400)) ;
	CCMenu *pBackground = CCMenu::create(pBackgroundItem, NULL) ;
	pBackground->setPosition(ccp(0, 0)) ;
	this->addChild(pBackground, 0) ;

	CCSprite *pListSpace[3] ;
	for(i=0; i<3; i++)
	{
		pListSpace[i] = CCSprite::create("Image/Member/List_Space.png") ;
		pListSpace[i]->setPosition(ccp(640, 590 - (i * 145))) ;
		this->addChild(pListSpace[i], 1) ;
	}

	// 마피아 초상화
	CCSprite *pMafia[3] ;
	for(i=0; i<3; i++)
	{
		pMafia[i] = CCSprite::create("Image/Member/Mafia_90.png") ;
		pMafia[i]->setPosition(ccp(320, 590 - (i * 145))) ;
		this->addChild(pMafia[i], 2) ;

		m_pMafia[i] = CCSprite::create("Image/Member/Image_Mafia_90.png") ;
		m_pMafia[i]->setPosition(ccp(320, 590 - (i * 145))) ;
		m_pMafia[i]->setVisible(false) ;
		this->addChild(m_pMafia[i], 2) ;
	}

	// 아이템 공백
	CCSprite *pItemSpace[3][3] ;
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			pItemSpace[i][j] = CCSprite::create("Image/Member/Item_Space.png") ;
			pItemSpace[i][j]->setPosition(ccp(440 + (j * 100), 590 - (i * 145))) ;
			this->addChild(pItemSpace[i][j], 2) ;
		}
	}

	// 버튼
	for(i=0; i<3; i++)
	{
		m_pMoveButton[i] = CCMenuItemImage::create("Image/Member/Move_Button_1.png", "Image/Member/Move_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;
		m_pPassButton[i] = CCMenuItemImage::create("Image/Member/Pass_Button_1.png", "Image/Member/Pass_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;
		m_pItemBuyButton[i] = CCMenuItemImage::create("Image/Member/Item_Buy_Button_1.png", "Image/Member/Item_Buy_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;

		m_pMoveButton[i]->setPosition(ccp(760, 590 - (i * 145))) ;
		m_pPassButton[i]->setPosition(ccp(m_pMoveButton[i]->getPosition().x + 100, m_pMoveButton[i]->getPosition().y)) ;
		m_pItemBuyButton[i]->setPosition(ccp(m_pPassButton[i]->getPosition().x + 100, m_pPassButton[i]->getPosition().y)) ;

		m_pMoveButton[i]->setTag(0 + (i*3)) ;
		m_pPassButton[i]->setTag(1 + (i*3)) ;
		m_pItemBuyButton[i]->setTag(2 + (i*3)) ;
	}

	CCMenuItemImage *pCloseButton = CCMenuItemImage::create("Image/Member/Close_Button_1.png", "Image/Member/Close_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;
	pCloseButton->setPosition(ccp(934, 182.5)) ;
	pCloseButton->setTag(9) ;

	CCMenu *pMenu = CCMenu::create(m_pMoveButton[0], m_pPassButton[0], m_pItemBuyButton[0],
								   m_pMoveButton[1], m_pPassButton[1], m_pItemBuyButton[1],
								   m_pMoveButton[2], m_pPassButton[2], m_pItemBuyButton[2],
								   pCloseButton, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pMenu, 2) ;

	return true ;
}

void CMemberControlPopup::SetMemberData(CMemberIcon *pMemberIcon)
{
	m_pMemberIcon = pMemberIcon ;
	SetMemberEnabled() ;
}

void CMemberControlPopup::SetMemberEnabled()
{
	int i ;
	const int num = m_pMemberIcon->m_Member.size() ;

	for(i=num; i<3; i++)
		MemberEnabled(i, false) ;

	for(i=0; i<num; i++)
		MemberEnabled(i, true) ;

	////
	CArea *Area = (CArea*)m_pMemberIcon->getParent() ;
	if(!g_pAreaManager->MoveRouteCheck(Area))
	{
		for(i=0; i<num; i++)
		{
			if(m_pMoveButton[i]->isEnabled())
			{
				m_pMoveButton[i]->setNormalImage(CCSprite::create("Image/Member/Move_Button_2.png")) ;
				m_pMoveButton[i]->setEnabled(false) ;
			}
		}
	}
	////
}

void CMemberControlPopup::MemberEnabled(int nIndex, bool bEnabled)
{
	if(bEnabled)
	{
		m_pMoveButton[nIndex]->setNormalImage(CCSprite::create("Image/Member/Move_Button_1.png")) ;
		m_pPassButton[nIndex]->setNormalImage(CCSprite::create("Image/Member/Pass_Button_1.png")) ;
		m_pItemBuyButton[nIndex]->setNormalImage(CCSprite::create("Image/Member/Item_Buy_Button_1.png")) ;
	}
	else
	{
		m_pMoveButton[nIndex]->setNormalImage(CCSprite::create("Image/Member/Move_Button_2.png")) ;
		m_pPassButton[nIndex]->setNormalImage(CCSprite::create("Image/Member/Pass_Button_2.png")) ;
		m_pItemBuyButton[nIndex]->setNormalImage(CCSprite::create("Image/Member/Item_Buy_Button_2.png")) ;
	}

	m_pMafia[nIndex]->setVisible(bEnabled) ;
	m_pMoveButton[nIndex]->setEnabled(bEnabled) ;
	m_pPassButton[nIndex]->setEnabled(bEnabled) ;
	m_pItemBuyButton[nIndex]->setEnabled(bEnabled) ;
}

void CMemberControlPopup::Menu_Click(CCObject *pSender)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	CCMenuItem *Item = (CCMenuItem *)pSender ;
	const int tag = Item->getTag() ;
	CArea *Area ;

	m_nTargetIndex = tag/3 ;

	switch(tag)
	{
	case 0 :
	case 3 :
	case 6 :
		Area = (CArea*)m_pMemberIcon->getParent() ;
		g_pAreaManager->MoveMember(Area) ;
		pDirector->popScene() ;
		break ;

	case 1 :
	case 4 :
	case 7 :
		break ;

	case 2 :
	case 5 :
	case 8 :
		break ;

	case 9 :
		pDirector->popScene() ;
		break ;
	}
}
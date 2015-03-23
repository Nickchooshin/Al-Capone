#include "BusinessBuilding.h"

#include "PopupMenu.h"
#include "Data.h"

bool CBusinessBuilding::init()
{
	m_bOwnership = false ;
	m_bActive = false ;
	m_bAllocate = false ;
	m_bHide = false ;

	m_pIconItem = CCMenuItemImage::create("Image/Building/Business_1.png", "Image/Building/Business_2.png", this, menu_selector(CBusinessBuilding::Click_Building)) ;

	CCMenu *pMenu = CCMenu::create(m_pIconItem, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pMenu) ;

	return true ;
}

void CBusinessBuilding::TurnFlow()
{
	if(!m_bActive && m_bOwnership)
	{
		m_bActive = true ;
	}
	else if(m_bAllocate && !m_bHide)
	{
		// 생산비
		g_pData->m_User.m_nMoney += g_pData->m_nProduction ;
	}
}

void CBusinessBuilding::RoundFlow()
{
	if(m_bOwnership)
	{
		// 유지비
		g_pData->m_User.m_nMoney -= g_pData->m_nMaintenance ;
	}
}

bool CBusinessBuilding::Inspection()
{
	if(m_bAllocate && !m_bHide)
	{
		g_pData->m_User.m_nHaveMember -= 1 ;

		SetState(OWN) ;
	}

	return true ;
}

void CBusinessBuilding::Click_Building(CCObject *pSender)
{
	if(!m_bOwnership && !CBuilding::m_bBuyBusiness)
	{
		SetPopupMenu("Image/Building/B_Buy_Button_1.png", "Image/Building/B_Buy_Button_2.png", OWN) ;
	}
	else if(m_bActive && !m_bAllocate)
	{
		SetPopupMenu("Image/Building/B_Allocate_Button_1.png", "Image/Building/B_Allocate_Button_2.png", ALLOCATE) ;
	}
	else if(m_bAllocate && !m_bHide)
	{
		SetPopupMenu("Image/Building/B_hide_Button_1.png", "Image/Building/B_hide_Button_2.png", HIDE) ;
	}
	else if(m_bAllocate && m_bHide)
	{
		SetPopupMenu("Image/Building/B_Allocate_Button_1.png", "Image/Building/B_Allocate_Button_2.png", UNHIDE) ;
	}
}

void CBusinessBuilding::Click_Menu(CCObject *pSender)
{
	CCMenuItem *pItem = (CCMenuItem *)pSender ;
	const int tag = pItem->getTag() ;
	bool bRelease=false ;

	switch(tag)
	{
	case OWN :
		if(g_pData->m_User.m_nMoney >= g_pData->m_nPayBuilding)
		{
			bRelease = true ;
			g_pData->m_User.m_nMoney -= g_pData->m_nPayBuilding ;
			CBuilding::m_bBuyBuilding = true ;
			CBuilding::m_bBuyBusiness = true ;

			SetState(OWN) ;
		}
		break ;

	case ALLOCATE :
		if(g_pData->m_User.m_nStandbyMember > 0)
		{
			bRelease = true ;
			g_pData->m_User.m_nStandbyMember -= 1 ;

			SetState(ALLOCATE) ;
		}
		break ;

	case HIDE :
		bRelease = true ;

		SetState(HIDE) ;
		break ;

	case UNHIDE :
		bRelease = true ;

		SetState(UNHIDE) ;
	}

	if(bRelease)
		g_pPopupMenu->Release() ;
}

void CBusinessBuilding::SetPopupMenu(const char *normalImage, const char *selectedImage, const int tag)
{
	CCMenuItemImage *pMenuItem = CCMenuItemImage::create(normalImage, selectedImage, this, menu_selector(CBusinessBuilding::Click_Menu)) ;
	pMenuItem->setAnchorPoint(ccp(0, 0)) ;
	pMenuItem->setPosition(ccp( m_pIconItem->getPosition().x + m_pIconItem->getContentSize().width/2,
								m_pIconItem->getPosition().y )) ;
	pMenuItem->setTag(tag) ;

	g_pPopupMenu->Release() ;
	g_pPopupMenu->m_pMenu = CCMenu::create(pMenuItem, NULL) ;
	g_pPopupMenu->m_pMenu->setPosition(ccp(0, 0)) ;

	this->addChild(g_pPopupMenu->m_pMenu) ;
}

void CBusinessBuilding::SetState(BUSINESS_STATE State)
{
	switch(State)
	{
	case OWN :
		m_bOwnership = true ;
		m_bAllocate = false ;
		m_bHide = false ;
		m_pIconItem->setNormalImage(CCSprite::create("Image/Building/Business_2.png")) ;
		m_pIconItem->setSelectedImage(CCSprite::create("Image/Building/Business_1.png")) ;
		break ;

	case ALLOCATE :
		m_bAllocate = true ;
		m_pIconItem->setNormalImage(CCSprite::create("Image/Building/Business_3.png")) ;
		break ;

	case HIDE :
		m_bHide = true ;
		m_pIconItem->setNormalImage(CCSprite::create("Image/Building/Business_4.png")) ;
		break ;

	case UNHIDE :
		m_bHide = false ;
		m_pIconItem->setNormalImage(CCSprite::create("Image/Building/Business_3.png")) ;
		break ;
	}
}
#include "SmugglingRoute.h"

#include "PopupMenu.h"
#include "Data.h"

bool CSmugglingRoute::init()
{
	m_bOwnership = false ;
	m_bHighlight = false ;

	m_pIconItem = CCMenuItemImage::create("Image/Building/Circulation_1.png", "Image/Building/Circulation_2.png", this, menu_selector(CSmugglingRoute::Click_Building)) ;
	CCMenu *pMenu = CCMenu::create(m_pIconItem, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
	m_pIconItem->setVisible(false) ;
	this->addChild(pMenu) ;

	return true ;
}

void CSmugglingRoute::TurnFlow()
{
}

void CSmugglingRoute::RoundFlow()
{
	if(m_bOwnership)
	{
		// À¯Áöºñ
		g_pData->m_User.m_nMoney -= g_pData->m_nMaintenance ;
	}
}

void CSmugglingRoute::setEnabled(bool bEnabled)
{
	m_pIconItem->setEnabled(bEnabled) ;
}

void CSmugglingRoute::Click_Building(CCObject *pSender)
{
	if(m_bHighlight)
	{
		SetPopupMenu("Image/Building/B_Move_Button_1.png", "Image/Building/B_Move_Button_2.png", 1) ;
	}
	else if(!m_bOwnership && !CBuilding::m_bBuyRoute)
	{
		SetPopupMenu("Image/Building/B_Buy_Button_1.png", "Image/Building/B_Buy_Button_2.png", 0) ;
	}
}

void CSmugglingRoute::Click_Menu(CCObject *pSender)
{
	CCMenuItem *Item = (CCMenuItem *)pSender ;
	const int tag = Item->getTag() ;

	switch(tag)
	{
	case 0 :
		if(g_pData->m_User.m_nMoney >= g_pData->m_nPayBuilding)
		{
			g_pPopupMenu->Release() ;

			g_pData->m_User.m_nMoney -= g_pData->m_nPayBuilding ;
			CBuilding::m_bBuyBuilding = true ;
			CBuilding::m_bBuyRoute = true ;
			m_bOwnership = true ;

			m_pIconItem->setNormalImage(CCSprite::create("Image/Building/Circulation_2.png")) ;
			//m_pIconItem->setSelectedImage(CCSprite::create("Image/Building/Circulation_1.png")) ;
		}
		break ;

	case 1 :
		break ;
	}
}

void CSmugglingRoute::SetPopupMenu(const char *normalImage, const char *selectedImage, const int tag)
{
	CCMenuItemImage *pMenuItem = CCMenuItemImage::create(normalImage, selectedImage, this, menu_selector(CSmugglingRoute::Click_Menu)) ;
	pMenuItem->setAnchorPoint(ccp(0, 0)) ;
	pMenuItem->setPosition(ccp( m_pIconItem->getPosition().x + m_pIconItem->getContentSize().width/2,
								m_pIconItem->getPosition().y )) ;
	pMenuItem->setTag(tag) ;

	g_pPopupMenu->Release() ;
	g_pPopupMenu->m_pMenu = CCMenu::create(pMenuItem, NULL) ;
	g_pPopupMenu->m_pMenu->setPosition(ccp(0, 0)) ;

	this->addChild(g_pPopupMenu->m_pMenu) ;
}

void CSmugglingRoute::RouteLinked()
{
	m_pIconItem->setVisible(true) ;
}

void CSmugglingRoute::RouteHighlight()
{
	m_bHighlight = true ;
	m_pIconItem->setNormalImage(CCSprite::create("Image/Building/Circulation_3.png")) ;
}
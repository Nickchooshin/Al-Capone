#include "SmugglingRoute.h"

#include "PopupMenu.h"
#include "Data.h"

bool CSmugglingRoute::init()
{
	m_bOwnership = false ;

	m_pIconItem = CCMenuItemImage::create("Image/Temp/temp_icon_d.png", "Image/Temp/temp_icon_dL.png", this, menu_selector(CSmugglingRoute::Click_Building)) ;
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

void CSmugglingRoute::Click_Building(CCObject *pSender)
{
	if(!m_bOwnership && !CBuilding::m_bBuyRoute)
	{
		CCMenuItemImage *pMenuItem = CCMenuItemImage::create("Image/Building/B_Buy_Button_1.png", "Image/Building/B_Buy_Button_2.png", this, menu_selector(CSmugglingRoute::Click_Menu)) ;
		pMenuItem->setAnchorPoint(ccp(0, 0)) ;
		pMenuItem->setPosition(ccp( m_pIconItem->getPosition().x + m_pIconItem->getContentSize().width/2,
									m_pIconItem->getPosition().y )) ;
		g_pPopupMenu->Release() ;
		g_pPopupMenu->m_pMenu = CCMenu::create(pMenuItem, NULL) ;
		g_pPopupMenu->m_pMenu->setPosition(ccp(0, 0)) ;
		this->addChild(g_pPopupMenu->m_pMenu) ;
	}
}

void CSmugglingRoute::Click_Menu(CCObject *pSender)
{
	if(g_pData->m_User.m_nMoney >= g_pData->m_nPayBuilding)
	{
		g_pPopupMenu->Release() ;

		g_pData->m_User.m_nMoney -= g_pData->m_nPayBuilding ;
		CBuilding::m_bBuyBuilding = true ;
		CBuilding::m_bBuyRoute = true ;
		m_bOwnership = true ;

		m_pIconItem->setNormalImage(CCSprite::create("Image/Temp/temp_icon_dL.png")) ;
		m_pIconItem->setSelectedImage(CCSprite::create("Image/Temp/temp_icon_d.png")) ;
	}
}

void CSmugglingRoute::RouteLinked()
{
	m_pIconItem->setVisible(true) ;
}
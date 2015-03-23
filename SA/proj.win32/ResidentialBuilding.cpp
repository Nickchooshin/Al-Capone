#include "ResidentialBuilding.h"

#include "PopupMenu.h"
#include "Data.h"

bool CResidentialBuilding::init()
{
	m_bOwnership = false ;

	m_pIconItem = CCMenuItemImage::create("Image/Building/hom_1.png", "Image/Building/hom_2.png", this, menu_selector(CResidentialBuilding::Click_Building)) ;
	CCMenu *pMenu = CCMenu::create(m_pIconItem, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pMenu) ;

	return true ;
}

void CResidentialBuilding::TurnFlow()
{
}

void CResidentialBuilding::RoundFlow()
{
	if(m_bOwnership)
	{
		// À¯Áöºñ
		g_pData->m_User.m_nMoney -= g_pData->m_nMaintenance ;
	}
}

void CResidentialBuilding::Click_Building(CCObject *pSender)
{
	if(!m_bOwnership)
	{
		CCMenuItemImage *pMenuItem = CCMenuItemImage::create("Image/Temp/temp_menu_buy.png", "Image/Temp/temp_menu_buy.png", this, menu_selector(CResidentialBuilding::Click_Menu)) ;
		pMenuItem->setAnchorPoint(ccp(0, 0)) ;
		pMenuItem->setPosition(ccp( m_pIconItem->getPosition().x + m_pIconItem->getContentSize().width/2,
									m_pIconItem->getPosition().y )) ;
		g_pPopupMenu->Release() ;
		g_pPopupMenu->m_pMenu = CCMenu::create(pMenuItem, NULL) ;
		g_pPopupMenu->m_pMenu->setPosition(ccp(0, 0)) ;
		this->addChild(g_pPopupMenu->m_pMenu) ;
	}
}

void CResidentialBuilding::Click_Menu(CCObject *pSender)
{
	if(g_pData->m_User.m_nMoney >= g_pData->m_nPayBuilding)
	{
		g_pPopupMenu->Release() ;

		g_pData->m_User.m_nMoney -= g_pData->m_nPayBuilding ;
		CBuilding::m_bBuyBuilding = true ;
		CBuilding::m_bBuyResidential = true ;
		m_bOwnership = true ;

		m_pIconItem->setNormalImage(CCSprite::create("Image/Building/hom_2.png")) ;
		m_pIconItem->setSelectedImage(CCSprite::create("Image/Building/hom_1.png")) ;
	}
}
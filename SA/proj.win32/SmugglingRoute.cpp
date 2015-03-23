#include "SmugglingRoute.h"

#include "Data.h"

bool CSmugglingRoute::init()
{
	m_bOwnership = false ;

	m_pIconItem = CCMenuItemImage::create("Image/Temp/temp_icon_d.png", "Image/Temp/temp_icon_dL.png", this, menu_selector(CSmugglingRoute::Click_Building)) ;
	CCMenu *pMenu = CCMenu::create(m_pIconItem, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
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
}

void CSmugglingRoute::Click_Menu(CCObject *pSender)
{
}
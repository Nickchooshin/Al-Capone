#include "ResidentialBuilding.h"

#include "PopupMenu.h"
#include "Data.h"
#include "MemberManager.h"

bool CResidentialBuilding::init()
{
	m_bOwnership = false ;

	m_pIconItem = CCMenuItemImage::create("Image/Building/Home_1_1.png", "Image/Building/Home_1_2.png", this, menu_selector(CResidentialBuilding::Click_Building)) ;
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
	if(!m_bOwnership && !CBuilding::m_bBuyResidential)
	{
		SetPopupMenu("Image/Building/B_Buy_Button_1.png", "Image/Building/B_Buy_Button_2.png", 0) ;
	}
	else if(m_bOwnership)
	{
		SetPopupMenu("Image/Building/B_Allocate_Button_1.png", "Image/Building/B_Allocate_Button_2.png", 1) ;
	}
}

void CResidentialBuilding::Click_Menu(CCObject *pSender)
{
	CCMenuItem *pItem = (CCMenuItem *)pSender ;
	const int tag = pItem->getTag() ;
	bool bRelease=false ;

	switch(tag)
	{
	case 0 :
		if(g_pData->m_User.m_nMoney >= g_pData->m_nPayBuilding)
		{
			bRelease = true ;
			g_pData->m_User.m_nMoney -= g_pData->m_nPayBuilding ;
			CBuilding::m_bBuyBuilding = true ;
			CBuilding::m_bBuyResidential = true ;
			m_bOwnership = true ;

			m_pIconItem->setNormalImage(CCSprite::create("Image/Building/Home_2_1.png")) ;
			m_pIconItem->setSelectedImage(CCSprite::create("Image/Building/Home_2_2.png")) ;
		}
		break ;
		 
	case 1 :
		if(g_pData->m_User.m_nStandbyMember > 0)
		{
			if(g_pMemberManager->AddMember(this))
			{
				bRelease = true ;
				g_pData->m_User.m_nStandbyMember -= 1 ;
			}
		}
		break ;
	}

	if(bRelease)
		g_pPopupMenu->Release() ;
}

void CResidentialBuilding::SetPopupMenu(const char *normalImage, const char *selectedImage, const int tag)
{
	CCMenuItemImage *pMenuItem = CCMenuItemImage::create(normalImage, selectedImage, this, menu_selector(CResidentialBuilding::Click_Menu)) ;
	pMenuItem->setAnchorPoint(ccp(0, 0)) ;
	pMenuItem->setPosition(ccp( m_pIconItem->getPosition().x + m_pIconItem->getContentSize().width/2,
								m_pIconItem->getPosition().y )) ;
	pMenuItem->setTag(tag) ;

	/*g_pPopupMenu->Release() ;
	g_pPopupMenu->m_pMenu = CCMenu::create(pMenuItem, NULL) ;
	g_pPopupMenu->m_pMenu->setPosition(ccp(0, 0)) ;

	this->addChild(g_pPopupMenu->m_pMenu) ;*/

	CCNode *Parent = this->getParent()->getParent() ;
	CCPoint Point ;
	Point = this->getPosition() + this->getParent()->getPosition() ;

	g_pPopupMenu->Release() ;
	g_pPopupMenu->m_pMenu = CCMenu::create(pMenuItem, NULL) ;
	g_pPopupMenu->m_pMenu->setPosition(Point) ;

	Parent->addChild(g_pPopupMenu->m_pMenu, 2) ;
}
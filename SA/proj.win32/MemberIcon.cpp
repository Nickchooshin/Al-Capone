#include "MemberIcon.h"

#include "MemberManager.h"

bool CMemberIcon::init()
{
	CCMenuItemImage *pMemberItem = CCMenuItemImage::create("Image/Temp/Man_Icon.png", "Image/Temp/Man_Icon2.png", this, menu_selector(CMemberIcon::Icon_Click)) ;
	CCMenu *pMenu = CCMenu::create(pMemberItem, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pMenu) ;

	return true ;
}

void CMemberIcon::Icon_Click(CCObject *pSender)
{
	//g_pMemberManager->ShowMenu(true) ;
	g_pMemberManager->ShowMenu() ;
}
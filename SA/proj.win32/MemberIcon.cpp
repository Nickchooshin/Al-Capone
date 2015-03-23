#include "MemberIcon.h"

#include "MemberManager.h"

bool CMemberIcon::init()
{
	m_pMemberItem = CCMenuItemImage::create("Image/Temp/Man_Icon.png", "Image/Temp/Man_Icon2.png", this, menu_selector(CMemberIcon::Icon_Click)) ;
	CCMenu *pMenu = CCMenu::create(m_pMemberItem, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pMenu) ;

	scheduleUpdate() ;

	return true ;
}

void CMemberIcon::update(float dt)
{
	if(!m_Member.empty())
		setVisible(true) ;
	else
		setVisible(false) ;
}

void CMemberIcon::Icon_Click(CCObject *pSender)
{
	g_pMemberManager->ShowMenu(this) ;
}

void CMemberIcon::setEnabled(bool bEnabled)
{
	m_pMemberItem->setEnabled(bEnabled) ;
}

bool CMemberIcon::AddMember(CMember &Member)
{
	const int num = m_Member.size() ;

	if(num==3)
		return false ;

	m_Member.push_back(Member) ;

	return true ;
}
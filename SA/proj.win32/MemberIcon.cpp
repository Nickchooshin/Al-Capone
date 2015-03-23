#include "MemberIcon.h"

#include "MemberManager.h"
#include "AreaManager.h"

#include "Data.h"

#include "SimpleAudioEngine.h"

bool CMemberIcon::init()
{
	m_bMove = false ;

	m_pMemberItem = CCMenuItemImage::create("Image/Game/Member/Man_Icon_1_1.png", "Image/Game/Member/Man_Icon_1_2.png", this, menu_selector(CMemberIcon::Icon_Click)) ;
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

void CMemberIcon::TurnFlow()
{
	int i ;
	int n=m_Member.size() ;

	for(i=0; i<n; i++)
	{
		m_Member[i].TurnFlow() ;
	}
}

void CMemberIcon::Inspection()
{
	const int num = m_Member.size() ;

	g_pData->m_User.m_nHaveMember -= num ;

	if(num!=0)
	{
		m_Member.clear() ;

		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Man_del.mp3") ;
	}
}

void CMemberIcon::Icon_Click(CCObject *pSender)
{
	if(!m_bMove)
	{
		g_pMemberManager->ShowMenu(this) ;
	}
	else
	{
		g_pAreaManager->MoveMemberFinish() ;
		setMove(false) ;
	}
}

bool CMemberIcon::AddMember(CMember &Member)
{
	const int num = m_Member.size() ;

	if(num==3)
		return false ;

	m_Member.push_back(Member) ;

	return true ;
}

void CMemberIcon::setMove(bool bMove)
{
	if(bMove && !m_bMove)
	{
		m_pMemberItem->setNormalImage(CCSprite::create("Image/Game/Member/Man_Icon_2_1.png")) ;
		m_pMemberItem->setSelectedImage(CCSprite::create("Image/Game/Member/Man_Icon_2_2.png")) ;
	}
	else if(!bMove && m_bMove)
	{
		m_pMemberItem->setNormalImage(CCSprite::create("Image/Game/Member/Man_Icon_1_1.png")) ;
		m_pMemberItem->setSelectedImage(CCSprite::create("Image/Game/Member/Man_Icon_1_2.png")) ;
	}

	m_bMove = bMove ;
}

void CMemberIcon::setEnabled(bool bEnabled)
{
	if(m_bMove)
		bEnabled = true ;
	m_pMemberItem->setEnabled(bEnabled) ;
}
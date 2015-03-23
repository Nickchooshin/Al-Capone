#include "MemberManager.h"

#include "Member.h"
#include "MemberIcon.h"
#include "MemberControlPopup.h"
#include "Building.h"
#include "Area.h"

CMemberManager::CMemberManager()
{
}

CMemberManager* CMemberManager::GetInstance()
{
	static CMemberManager MemberManager ;

	return &MemberManager ;
}

bool CMemberManager::init()
{
	int i, j ;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//m_pControlUI = CMemberControlUI::create() ;
	//m_pControlUI->setVisible(false) ;
	//this->addChild(m_pControlUI, 4) ;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			m_pMemberIcon[i][j] = CMemberIcon::create() ;
			m_pMemberIcon[i][j]->setPosition(ccp( j * 200 + 150, visibleSize.height - (i * 150) - 100 )) ;
			m_pMemberIcon[i][j]->setVisible(false) ;
			this->addChild(m_pMemberIcon[i][j], 2) ;
		}
	}

	return true ;
}

bool CMemberManager::AddMember(CBuilding *Building)
{
	CArea *pArea = (CArea*)Building->getParent() ;
	const int tag = pArea->getTag() ;

	CMember Temp ;
	if(m_pMemberIcon[tag/4][tag%4]->AddMember(Temp) == false)
		return false ;

	m_pMemberIcon[tag/4][tag%4]->setVisible(true) ;

	return true ;
}

void CMemberManager::ShowMenu(std::vector<CMember> &Member)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	g_pMemberControlPopup->SetMemberData(Member) ;
	pDirector->pushScene(g_pMemberControlPopup) ;
}
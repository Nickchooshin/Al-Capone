#include "MemberManager.h"

#include "MemberIcon.h"
#include "MemberControlPopup.h"
#include "Building.h"
#include "Area.h"
#include "Manager.h"

CMemberManager::CMemberManager()
{
}

bool CMemberManager::init()
{
	m_nTag = -1 ;
	m_pMemberIcon = NULL ;
	m_nIndex = -1 ;

	return true ;
}

bool CMemberManager::AddMember(CBuilding *Building)
{
	CArea *pArea = (CArea*)Building->getParent() ;
	const int tag = pArea->getTag() ;

	CMember Temp ;
	//if(m_pMemberIcon[tag/4][tag%4]->AddMember(Temp) == false)
	//	return false ;

	return pArea->m_pMemberIcon->AddMember(Temp) ;
}

void CMemberManager::ShowMenu(CMemberIcon *pMemberIcon)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	g_pMemberControlPopup->SetMemberData(pMemberIcon) ;
	pDirector->pushScene(g_pMemberControlPopup) ;
}

void CMemberManager::MemorizeMovingData(int nTag, CMemberIcon *pMemberIcon, int nIndex)
{
	m_nTag = nTag ;
	m_pMemberIcon = pMemberIcon ;
	m_nIndex = nIndex ;
}

bool CMemberManager::MovingData(int Way)
{
	bool bSuccess ;
	int x1=m_nTag%4, x2=x1 ;
	int y1=m_nTag/4, y2=y1 ;

	switch(Way)
	{
	case CAreaManager::WAY_UP :
		y2 -= 1 ;
		break ;

	case CAreaManager::WAY_DOWN :
		y2 += 1 ;
		break ;

	case CAreaManager::WAY_LEFT :
		x2 -= 1 ;
		break ;

	case CAreaManager::WAY_RIGHT :
		x2 += 1 ;
		break ;
	}

	std::vector<CMember> &Member1 = CManager::Area->m_Area[y1][x1]->m_pMemberIcon->m_Member ;
	CMemberIcon &Member2 = *CManager::Area->m_Area[y2][x2]->m_pMemberIcon ;

	CMember Temp = Member1[m_nIndex] ;
	Temp.setMove(true) ;
	bSuccess = Member2.AddMember(Temp) ;
	if(bSuccess)
	{
		Member1.erase(Member1.begin()+m_nIndex) ;

		CManager::Area->MoveMemberFinish() ;
		m_pMemberIcon->setMove(false) ;

		m_nTag = -1 ;
		m_pMemberIcon = NULL ;
		m_nIndex = -1 ;
	}

	return bSuccess ;
}
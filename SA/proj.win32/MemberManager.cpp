#include "MemberManager.h"

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
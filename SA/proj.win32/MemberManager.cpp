#include "MemberManager.h"

#include "MemberIcon.h"
#include "MemberControlUI.h"
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

void CMemberManager::AddMember(CBuilding *Building)
{
	CArea *pArea = (CArea*)Building->getParent() ;
	const int tag = pArea->getTag() ;

	m_pMemberIcon[tag/4][tag%4]->setVisible(true) ;
}

void CMemberManager::ShowMenu()
{
	//m_pControlUI->setVisible(bVisible) ;
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->pushScene(CMemberControlUI::create()) ;
}
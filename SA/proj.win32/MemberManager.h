#ifndef __MEMBER_MANAGER_H__
#define __MEMBER_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CMemberIcon ;
class CMemberControlUI ;
class CBuilding ;

class CMemberManager : public CCNode
{
private :
	CMemberIcon *m_pMemberIcon[4][4] ;
	//CMemberControlUI *m_pControlUI ;

public :
	static CMemberManager* GetInstance() ;

	bool init() ;

	void AddMember(CBuilding *Building) ;
	void ShowMenu() ;
private :
	CMemberManager() ;
} ;

#define g_pMemberManager CMemberManager::GetInstance()

#endif
#ifndef __MEMBER_MANAGER_H__
#define __MEMBER_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CMemberIcon ;
class CBuilding ;

class CMemberManager : public CCNode
{
private :

public :
	static CMemberManager* GetInstance() ;

	bool init() ;

	bool AddMember(CBuilding *Building) ;
	void ShowMenu(CMemberIcon *pMemberIcon) ;
private :
	CMemberManager() ;
} ;

#define g_pMemberManager CMemberManager::GetInstance()

#endif
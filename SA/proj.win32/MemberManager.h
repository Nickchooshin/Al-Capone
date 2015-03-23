#ifndef __MEMBER_MANAGER_H__
#define __MEMBER_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CMemberIcon ;
class CBuilding ;

class CMemberManager : public CCNode
{
private :
	int m_nTag ;
	CMemberIcon *m_pMemberIcon ;
	int m_nIndex ;

public :
	bool init() ;

	CREATE_FUNC(CMemberManager) ;

	bool AddMember(CBuilding *Building) ;
	void ShowMenu(CMemberIcon *pMemberIcon) ;
	void MemorizeMovingData(int nTag, CMemberIcon *pMemberIcon, int nIndex) ;
	bool MovingData(int Way) ;
private :
	CMemberManager() ;
} ;

#endif
#ifndef __BUSINESS_BUILDING_H__
#define __BUSINESS_BUILDING_H__

#include "Building.h"

class CBusinessBuilding : public CBuilding
{
private :
	bool m_bActive ;
	bool m_bAllocate ;
	bool m_bHide ;
	CCMenuItemImage *m_pMenuItem ;

	static enum BUSINESS_STATE { OWN=0, ALLOCATE, HIDE, UNHIDE } ;

public :
	bool init() ;

	CREATE_FUNC(CBusinessBuilding) ;

	void TurnFlow() ;
	void RoundFlow() ;

	void Inspection() ;
private :
	void Click_Building(CCObject *pSender) ;
	void Click_Menu(CCObject *pSender) ;
	void SetPopupMenu(const char *normalImage, const char *selectedImage, const int tag) ;
	void SetState(BUSINESS_STATE State) ;
} ;

#endif
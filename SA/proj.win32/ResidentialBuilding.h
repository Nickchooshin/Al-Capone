#ifndef __RESIDENTIAL_BUILDING_H__
#define __RESIDENTIAL_BUILDING_H__

#include "Building.h"

class CResidentialBuilding : public CBuilding
{
public:
	bool init() ;

	CREATE_FUNC(CResidentialBuilding) ;

	void TurnFlow() ;
	void RoundFlow() ;

private :
	void Click_Building(CCObject *pSender) ;
	void Click_Menu(CCObject *pSender) ;
} ;

#endif
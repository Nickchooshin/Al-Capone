#ifndef __SMUGGLING_ROUTE_H__
#define __SMUGGLING_ROUTE_H__

#include "Building.h"

class CSmugglingRoute : public CBuilding
{
public :
	bool init() ;

	CREATE_FUNC(CSmugglingRoute) ;

	void TurnFlow() ;
	void RoundFlow() ;

	void RouteLinked() ;

private :
	void Click_Building(CCObject *pSender) ;
	void Click_Menu(CCObject *pSender) ;
} ;

#endif
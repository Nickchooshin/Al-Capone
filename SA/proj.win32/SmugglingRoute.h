#ifndef __SMUGGLING_ROUTE_H__
#define __SMUGGLING_ROUTE_H__

#include "Building.h"

class CSmugglingRoute : public CBuilding
{
private :
	bool m_bHighlight ;
	int m_nWay ;

public :
	bool init() ;

	CREATE_FUNC(CSmugglingRoute) ;

	void TurnFlow() ;
	void RoundFlow() ;

	void setEnabled(bool bEnabled) ;

	void RouteLinked() ;
	void RouteHighlight(bool bEnabled) ;
	void SetRouteWay(int Way) ;
private :
	void Click_Building(CCObject *pSender) ;
	void Click_Menu(CCObject *pSender) ;
	void SetPopupMenu(const char *normalImage, const char *selectedImage, const int tag) ;
} ;

#endif
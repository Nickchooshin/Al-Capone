#ifndef __AREA_MANAGER_H__
#define __AREA_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CArea ;
class CSmugglingRoute ;

class CAreaManager : public CCNode
{
private :
	CArea *m_Area[4][4] ;
	CSmugglingRoute *m_SmugglingRoute[3][4][2] ;
public :
	static enum ROUTE_WAY { WAY_UP=0, WAY_DOWN, WAY_RIGHT, WAY_LEFT } ;

public :
	static CAreaManager* GetInstance() ;

	bool init() ;

	//CREATE_FUNC(CAreaManager) ;

	void update(float dt) ;

	void TurnFlow() ;
	void RoundFlow() ;

	bool MoveRouteCheck(CArea *Area) ;
	void MoveMemberPrepare(CArea *Area) ;
	void MoveMemberFinish() ;

	void AreaLinked(int x, int y) ;
	void AreaHighlightOn(int x, int y) ;
	void AreaHighlightOff() ;

	int GetOwnResidentialNumber() ;
private :
	CAreaManager() ;

	void MoveEnabled(bool bEnabled) ;

	void RouteHighlight(CSmugglingRoute *Route, CArea *Area, ROUTE_WAY Way) ;

	bool LoadAreaCoord(CCPoint AreaCoord[][4]) ; // CCPoint AreaCoord[][4] or CCPoint (*AreaCoord)[4]
	bool LoadRouteCoord(CCPoint RouteCoord[][4][2]) ;

	friend class CMemberManager ;
} ;

#define g_pAreaManager CAreaManager::GetInstance()

#endif
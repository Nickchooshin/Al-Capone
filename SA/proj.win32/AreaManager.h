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
	static CAreaManager* GetInstance() ;

	bool init() ;

	//CREATE_FUNC(CAreaManager) ;

	void update(float dt) ;

	void TurnFlow() ;
	void RoundFlow() ;

	void AreaLinked(int x, int y) ;

	int GetOwnResidentialNumber() ;
private :
	CAreaManager() ;
} ;

#define g_pAreaManager CAreaManager::GetInstance()

#endif
#ifndef __AREA_MANAGER_H__
#define __AREA_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CArea ;

class CAreaManager : public CCNode
{
private :
	CArea *m_Area[4][4] ;

public :
	bool init() ;

	CREATE_FUNC(CAreaManager) ;

	void update(float dt) ;

	void TurnFlow() ;
	void RoundFlow() ;

	int GetOwnResidentialNumber() ;
} ;

#endif
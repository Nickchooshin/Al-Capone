#ifndef __AREA_H__
#define __AREA_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CBuilding ;

class CArea : public CCNode
{
private :
	int m_nAttention ;
	int m_nBaseInspection ;
	bool m_bInspection[8] ;
	CCSprite *m_pBlockade ;
	CCNode *m_pTurnMark ;
	CBuilding *m_pBuilding[2] ;
public :
	static bool m_bInspectionView[8] ;

public :
	bool init() ;

	CREATE_FUNC(CArea) ;

	void SetBaseInspection(int turn) ;
	void SetInspection(int turn) ;

	void TurnFlow() ;
	void RoundFlow() ;

	void AreaLinked() ;

	bool GetOwnResidential() ;
private :
	void update(float dt) ;
} ;

#endif
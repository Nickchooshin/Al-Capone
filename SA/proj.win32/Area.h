#ifndef __AREA_H__
#define __AREA_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CBuilding ;
class CMemberIcon ;

class CArea : public CCNode
{
private :
	bool m_bSmuggling ;
	int m_nAttention ;
	int m_nBaseInspection ;
	bool m_bInspection[8] ;
	bool m_bBlockade ;
	CCSprite *m_pBlockade[2] ;
	CCNode *m_pTurnMark ;
	CCSprite *m_pAttentionSprite ;
	CCLabelTTF *m_pAttentionLabel ;
	CBuilding *m_pBuilding[2] ;
public :
	static bool m_bInspectionView[8] ;
	CMemberIcon *m_pMemberIcon ;

public :
	bool init(int Inspection) ;

	static CArea* create(int Inspection)
	{
		CArea *pRet = new CArea() ;
		if (pRet && pRet->init(Inspection))
		{
			pRet->autorelease() ;
		}
		else
		{
			delete pRet ;
			pRet = NULL ;
			return NULL ;
		}
	}

	void SetSmuggling(bool bSmuggling) ;
	//void SetBaseInspection(int turn) ;
	//void SetInspection(int turn) ;
	void setEnabled(bool bEnabled) ;
	void SetAreaBlockade(bool bEnabled) ;

	void AddAttention(int nAttention) ;

	void TurnFlow() ;
	void RoundFlow() ;

	void AreaLinked() ;

	bool GetOwnResidential() ;
	bool GetOwnBusiness() ;
	bool isSmuggling() ;
	bool isInspection() ;
private :
	void update(float dt) ;
} ;

#endif
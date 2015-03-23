#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CBuilding : public CCNode
{
protected :
	bool m_bOwnership ;
	CCMenuItemImage *m_pIconItem ;
public :
	static bool m_bBuyBuilding, m_bBuyBusiness, m_bBuyResidential, m_bBuyRoute ;

public :
	virtual bool init() = 0 ;

	virtual void TurnFlow() = 0 ;
	virtual void RoundFlow() = 0 ;

	void setEnabled(bool Enabled) { m_pIconItem->setEnabled(Enabled) ; }

	CCSize getIconSize() { return m_pIconItem->getContentSize() ; }
	bool getOwnership() { return m_bOwnership ; }
protected :
	virtual void Click_Building(CCObject *pSender) = 0 ;
	virtual void Click_Menu(CCObject *pSender) = 0 ;
} ;

#endif
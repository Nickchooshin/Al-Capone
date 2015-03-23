#ifndef __TURN_UI_H__
#define __TURN_UI_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CTurnUI : public CCNode
{
private :
	CCLabelTTF *pTurnLabel, *pRoundLabel ;

public :
	bool init() ;

	CREATE_FUNC(CTurnUI) ;

	void TurnFlow(CCObject *pSender) ;
} ;

#endif
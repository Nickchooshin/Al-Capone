#ifndef __MONEY_H__
#define __MONEY_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CMoneyUI : public CCNode
{
private :
	CCLabelTTF *m_pMoneyLabel ;

public :
	bool init() ;

	CREATE_FUNC(CMoneyUI) ;

	void update(float dt) ;
} ;

#endif
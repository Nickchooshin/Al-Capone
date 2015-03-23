#ifndef __INSPECTION_CHECK_UI_H__
#define __INSPECTION_CHECK_UI_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CInspectionCheckUI : public CCNode
{
public :
	bool init() ;

	CREATE_FUNC(CInspectionCheckUI) ;

	void Click_Menu(CCObject *pSender) ;
} ;

#endif
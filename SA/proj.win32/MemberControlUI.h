#ifndef __MEMBER_CONTROL_UI_H__
#define __MEMBER_CONTROL_UI_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CMemberControlUI : public CCScene
{
public :
	bool init() ;

	static CCScene* scene() ;

	CREATE_FUNC(CMemberControlUI) ;
private :
	void Menu_Click(CCObject *pSender) ;
} ;

#endif
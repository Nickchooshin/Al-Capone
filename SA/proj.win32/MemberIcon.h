#ifndef __MEMBER_ICON_H__
#define __MEMBER_ICON_H__

#include "cocos2d.h"
#include "Member.h"

using namespace cocos2d ;

class CMemberControlUI ;

class CMemberIcon : public CCNode
{
private :
	CMember m_Member[3] ;
	static CMemberControlUI *m_pControlUI ;

public :
	bool init() ;

	CREATE_FUNC(CMemberIcon) ;
private :
	void Icon_Click(CCObject *pSender) ;
} ;

#endif
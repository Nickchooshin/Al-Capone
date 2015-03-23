#ifndef __MEMBER_ICON_H__
#define __MEMBER_ICON_H__

#include "cocos2d.h"
#include "Member.h"
#include <vector>

using namespace cocos2d ;

class CMemberControlUI ;

class CMemberIcon : public CCNode
{
private :
	std::vector<CMember> m_Member ;
	static CMemberControlUI *m_pControlUI ;

public :
	bool init() ;

	CREATE_FUNC(CMemberIcon) ;

	bool AddMember(CMember &Member) ;
private :
	void Icon_Click(CCObject *pSender) ;
} ;

#endif
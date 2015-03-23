#ifndef __MEMBER_ICON_H__
#define __MEMBER_ICON_H__

#include "cocos2d.h"
#include "Member.h"
#include <vector>

using namespace cocos2d ;

class CMemberControlPopup ;

class CMemberIcon : public CCNode
{
private :
	CCMenuItemImage *m_pMemberItem ;
	std::vector<CMember> m_Member ;

public :
	bool init() ;

	CREATE_FUNC(CMemberIcon) ;

	void update(float dt) ;

	void setEnabled(bool bEnabled) ;

	bool AddMember(CMember &Member) ;
private :
	void Icon_Click(CCObject *pSender) ;

	friend CMemberControlPopup ;
} ;

#endif
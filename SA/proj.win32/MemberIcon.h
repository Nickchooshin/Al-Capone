#ifndef __MEMBER_ICON_H__
#define __MEMBER_ICON_H__

#include "cocos2d.h"
#include "Member.h"
#include <vector>

using namespace cocos2d ;

class CMemberManager ;
class CMemberControlPopup ;

class CMemberIcon : public CCNode
{
private :
	CCMenuItemImage *m_pMemberItem ;
	std::vector<CMember> m_Member ;
	bool m_bMove ;

public :
	bool init() ;

	CREATE_FUNC(CMemberIcon) ;

	void update(float dt) ;

	bool AddMember(CMember &Member) ;

	void setMove(bool bMove) ;
	void setEnabled(bool bEnabled) ;

	void TurnFlow() ;
private :
	void Icon_Click(CCObject *pSender) ;

	friend CMemberManager ;
	friend CMemberControlPopup ;
} ;

#endif
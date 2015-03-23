#ifndef __MEMBER_CONTROL_POPUP_H__
#define __MEMBER_CONTROL_POPUP_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CMember ;

class CMemberControlPopup : public CCScene
{
private :
	CCSprite *m_pMafia[3] ;
	CCMenuItemImage *m_pMoveButton[3] ;
	CCMenuItemImage *m_pPassButton[3] ;
	CCMenuItemImage *m_pItemBuyButton[3] ;

public :
	bool init() ;

	static CMemberControlPopup* GetInstance() ;

	static CCScene* scene() ;

	void SetMemberData(std::vector<CMember> &Member) ;
private :
	CMemberControlPopup() ;

	void Menu_Click(CCObject *pSender) ;
} ;

#define g_pMemberControlPopup CMemberControlPopup::GetInstance()

#endif
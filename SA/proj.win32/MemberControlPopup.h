#ifndef __MEMBER_CONTROL_POPUP_H__
#define __MEMBER_CONTROL_POPUP_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CMemberIcon ;

class CMemberControlPopup : public CCScene
{
private :
	CMemberIcon *m_pMemberIcon ;
	CCSprite *m_pMafia[3] ;
	CCMenuItemImage *m_pMoveButton[3] ;
	CCMenuItemImage *m_pPassButton[3] ;
	CCMenuItemImage *m_pItemBuyButton[3] ;
	int m_nTargetIndex ;

public :
	bool init() ;

	static CMemberControlPopup* GetInstance() ;

	//static CCScene* scene() ;

	void SetMemberData(CMemberIcon *pMemberIcon) ;
private :
	CMemberControlPopup() ;

	void SetMemberEnabled() ;
	void MemberEnabled(int nIndex, bool bEnabled) ;

	void Menu_Click(CCObject *pSender) ;
} ;

#define g_pMemberControlPopup CMemberControlPopup::GetInstance()

#endif
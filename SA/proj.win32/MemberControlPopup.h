#ifndef __MEMBER_CONTROL_POPUP_H__
#define __MEMBER_CONTROL_POPUP_H__

#include "cocos2d.h"
#include <vector>

using namespace cocos2d ;

class CMemberIcon ;

class CMemberControlPopup : public CCScene
{
private :
	CMemberIcon *m_pMemberIcon ;
	CCSprite *m_pMafia[3] ;
	CCSprite *m_pItemList[3][3] ;
	CCMenuItemImage *m_pMoveButton[3] ;
	CCMenuItemImage *m_pPassButton[3] ;
	CCMenuItemImage *m_pItemBuyButton[3] ;

public :
	bool init() ;

	static CMemberControlPopup* GetInstance() ;

	//static CCScene* scene() ;

	void SetMemberData(CMemberIcon *pMemberIcon) ;
	void UpdateItemList() ;
private :
	CMemberControlPopup() ;

	void SetMemberEnabled() ;
	void MemberEnabled(int nIndex, bool bEnabled) ;

	void Menu_Click(CCObject *pSender) ;
} ;

#define g_pMemberControlPopup CMemberControlPopup::GetInstance()

#endif
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
	CCMenuItemImage *m_pItemList[3][3] ;
	CCMenuItemImage *m_pMoveButton[3] ;
	CCMenuItemImage *m_pPassButton[3] ;
	CCMenuItemImage *m_pItemBuyButton[3] ;
	CCMenuItemImage *m_pCloseButton ;

	int m_nPassItemState ;
	int m_nSenderIndex, m_nReceiverIndex ;

public :
	bool init() ;

	static CMemberControlPopup* GetInstance() ;

	//static CCScene* scene() ;

	void SetMemberData(CMemberIcon *pMemberIcon) ;
	void SetAllButtonEnabled(int nIndex, bool bEnabled) ;

	void UpdateItemList() ;
private :
	CMemberControlPopup() ;

	void SetButtonEnabled(int Index, bool bEnabled, const char* ButtonName) ;
	void SetMemberEnabled() ;
	void MemberEnabled(int nIndex, bool bEnabled) ;

	void PassItemSender(int Index) ;
	void PassItemReceiver(int Index) ;
	void PassItem(int index) ;
	void PassItemEnd() ;

	void SellItem(int mIndex, int iIndex) ;

	void Menu_Click(CCObject *pSender) ;
} ;

#define g_pMemberControlPopup CMemberControlPopup::GetInstance()

#endif
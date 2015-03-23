#ifndef __ITEM_BUY_POPUP_H__
#define __ITEM_BUY_POPUP_H__

#include "cocos2d.h"
#include <vector>

using namespace cocos2d ;

class CMember ;

class CItemBuyPopup : public CCScene
{
private :
	std::vector<int> m_ItemList ;
	CMember *m_pMember ;
	CCMenuItemImage *m_pItem[3] ;

public :
	bool init() ;

	static CItemBuyPopup* GetInstance() ;

	void SetMemberData(CMember *pMember) ;
private :
	CItemBuyPopup() ;

	void SetItemList() ;
	bool AddItem(int type) ;

	void UpdateItemList() ;

	void Menu_Click(CCObject *pSender) ;
} ;

#endif

#define g_pItemBuyPopup CItemBuyPopup::GetInstance()
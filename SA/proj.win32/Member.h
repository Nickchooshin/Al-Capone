#ifndef __MEMBER_H__
#define __MEMBER_H__

#include "ItemData.h"

class CMemberControlPopup ;
class CItemBuyPopup ;

class CMember
{
private :
	bool m_bMove ;
	bool m_bBuy ;
	ITEM_TYPE m_ItemList[3] ;

public :
	CMember() ;
	~CMember() ;

	void setMove(bool bMove) ;
	void setBuy(bool bBuy) ;

	bool isMove() ;
	bool isBuy() ;

	void TurnFlow() ;

	friend CMemberControlPopup ;
	friend CItemBuyPopup ;
} ;

#endif
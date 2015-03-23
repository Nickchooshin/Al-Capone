#ifndef __MEMBER_H__
#define __MEMBER_H__

class CMemberControlPopup ;
class CItemBuyPopup ;

class CMember
{
public :
	static enum ITEM_TYPE { NOTHING=0, ACOHOL, ORIGINAL_DRINK, NARCOTIC } ;
private :
	bool m_bMove ;
	ITEM_TYPE m_ItemList[3] ;

public :
	CMember() ;
	~CMember() ;

	void setMove(bool bMove) ;

	bool isMove() ;

	friend CMemberControlPopup ;
	friend CItemBuyPopup ;
} ;

#endif
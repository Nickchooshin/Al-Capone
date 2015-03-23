#ifndef __MEMBER_H__
#define __MEMBER_H__

class CMember
{
public :
	static enum ITEM_TYPE { NOTHING=0 } ;
private :
	bool m_bMove ;
	ITEM_TYPE m_ItemList[3] ;

public :
	CMember() ;
	~CMember() ;
} ;

#endif
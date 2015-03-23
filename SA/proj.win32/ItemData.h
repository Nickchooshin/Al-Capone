#ifndef __ITEM_DATA_H__
#define __ITEM_DATA_H__

#include <string>

enum ITEM_TYPE { NOTHING=-1, ACOHOL, ORIGINAL_DRINK, NARCOTIC } ;

class CItemData
{
public :
	std::string m_sName[3] ;
	std::string m_sExplanation[3] ;
	int m_nBuy[3] ;
	int m_nSell[3] ;
	int m_nAttention[3] ;

public :
	CItemData()
	{
		for(int i=0; i<3; i++)
		{
			m_sName[i] = "" ;
			m_sExplanation[i] = "" ;
			m_nBuy[i] = 0 ;
			m_nSell[i] = 0 ;
			m_nAttention[i] = 0 ;
		}
	}
} ;

#endif
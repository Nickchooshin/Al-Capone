#ifndef __DATA_H__
#define __DATA_H__

#include "UserData.h"

class CData
{
public :
	CUserData m_User ;
	int m_nMaxCapacity ;
	int m_nPayBuilding, m_nPayMember ;
	int m_nMaintenance, m_nProduction ;
private :
	enum DATA_TYPE { NOTHING=0, MAX_CAPACITY, PAY_BUILDING, PAY_MEMBER, MAINTENANCE, PRODUCTION, MONEY, STANDBY_MEMBER } ;

private :
	CData() : m_nMaxCapacity(5),
				m_nPayBuilding(1), m_nPayMember(1),
				m_nMaintenance(1), m_nProduction(1)
	{}
public :
	static CData* GetInstance()
	{
		static CData Data ;

		return &Data ;
	}

	bool init() ;
} ;

#define g_pData CData::GetInstance()

#endif
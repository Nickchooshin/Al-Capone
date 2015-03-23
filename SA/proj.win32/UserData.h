#ifndef __USER_DATA_H__
#define __USER_DATA_H__

#include "Turn.h"

class CUserData
{
public :
	CTurn m_Turn ;
	int m_nOwnResidential ;
	int m_nHaveMember, m_nStandbyMember ;
	int m_nMoney ;

public :
	CUserData() : m_nOwnResidential(0),
					m_nMoney(5),
					m_nHaveMember(0),
					m_nStandbyMember(0)
	{}
} ;

#endif
#include "Turn.h"

int CTurn::m_nMaxTurn = 7 ;

CTurn::CTurn() : m_nRound(1), m_nTurn(1) , m_nTurnFlow(false)
{
}
CTurn::~CTurn()
{
}

void CTurn::TurnFlow()
{
	m_nTurnFlow = true ;
	m_nTurn += 1 ;

	if(m_nTurn>m_nMaxTurn)
	{
		m_nTurn -= m_nMaxTurn ;
		m_nRound += 1 ;
	}
}

void CTurn::operator++()
{
	TurnFlow() ;
}

const int CTurn::GetRound()
{
	return m_nRound ;
}

const int CTurn::GetTurn()
{
	return m_nTurn ;
}

bool CTurn::BeginTurnFlow()
{
	return m_nTurnFlow ;
}

void CTurn::EndTurnFlow()
{
	m_nTurnFlow = false ;
}
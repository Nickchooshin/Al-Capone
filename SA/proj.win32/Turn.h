#ifndef __TURN_H__
#define __TURN_H__

class CTurn
{
private :
	int m_nRound ;
	int m_nTurn ;
	bool m_nTurnFlow ;
	static int m_nMaxTurn ;

public:
	CTurn() ;
	~CTurn() ;

	void TurnFlow() ;

	void operator++() ;

	const int GetRound() ;
	const int GetTurn() ;

	bool BeginTurnFlow() ;
	void EndTurnFlow() ;
} ;

#endif
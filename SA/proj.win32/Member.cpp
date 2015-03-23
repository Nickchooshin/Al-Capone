#include "Member.h"

CMember::CMember() : m_bMove(false),
					 m_bBuy(false)
{
	for(int i=0; i<3; i++)
		m_ItemList[i] = NOTHING ;
}

CMember::~CMember()
{
}

void CMember::setMove(bool bMove)
{
	m_bMove = bMove ;
}

void CMember::setBuy(bool bBuy)
{
	m_bBuy = bBuy ;
}

bool CMember::isMove()
{
	return m_bMove ;
}

bool CMember::isBuy()
{
	return m_bBuy ;
}

void CMember::TurnFlow()
{
	setMove(false) ;
	setBuy(false) ;
}
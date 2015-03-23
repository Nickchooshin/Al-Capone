#include "Member.h"

CMember::CMember() : m_bMove(false)
{
	for(int i=0; i<3; i++)
		m_ItemList[i] = NOTHING ;
}

CMember::~CMember()
{
}
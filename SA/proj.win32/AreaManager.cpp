#include "AreaManager.h"
#include "Area.h"

#include "Data.h"

bool CAreaManager::init()
{
	int i, j ;
	int Inspection[6][6] ;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	for(i=1; i<=4; i++)
	{
		for(j=1; j<=4; j++)
		{
			while(1)
			{
				Inspection[i][j] = rand()%6+2 ;

				if((Inspection[i][j]!=Inspection[i][j-1]) && (Inspection[i][j]!=Inspection[i][j+1]) &&
					(Inspection[i][j]!=Inspection[i-1][j]) && (Inspection[i][j]!=Inspection[i+1][j]))
				{
					break ;
				}
			}
		}
	}

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			m_Area[i][j] = CArea::create() ;
			m_Area[i][j]->setPosition(ccp( j * 200 + 100, visibleSize.height - (i * 150) - 100 )) ;
			m_Area[i][j]->SetBaseInspection(Inspection[i+1][j+1]) ;
			this->addChild(m_Area[i][j]) ;
		}
	}

	scheduleUpdate() ;

	return true ;
}

void CAreaManager::update(float dt)
{
	if(g_pData->m_bBuyBuilding)
		g_pData->m_User.m_nOwnResidential = GetOwnResidentialNumber() ;
}

void CAreaManager::TurnFlow()
{
	int i, j ;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			m_Area[i][j]->TurnFlow() ;
		}
	}
}

void CAreaManager::RoundFlow()
{
	int i, j ;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			m_Area[i][j]->RoundFlow() ;
		}
	}
}

int CAreaManager::GetOwnResidentialNumber()
{
	int i, j ;
	int num=0 ;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(m_Area[i][j]->GetOwnResidential())
				num += 1 ;
		}
	}

	return num ;
}
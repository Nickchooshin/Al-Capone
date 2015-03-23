#include "AreaManager.h"
#include "Area.h"
#include "SmugglingRoute.h"

#include "Data.h"

bool CAreaManager::init()
{
	int i, j ;
	int Inspection[6][6] ;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	// 정기 검문 초기화
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

	// 지역 초기화
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			m_Area[i][j] = CArea::create() ;
			m_Area[i][j]->setPosition(ccp( j * 200 + 150, visibleSize.height - (i * 150) - 100 )) ;
			m_Area[i][j]->SetBaseInspection(Inspection[i+1][j+1]) ;
			this->addChild(m_Area[i][j]) ;
		}
	}

	// 경로 초기화
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			m_SmugglingRoute[i][j][0] = CSmugglingRoute::create() ;
			m_SmugglingRoute[i][j][0]->setPosition(ccp( i * 200 + 250, visibleSize.height - (j * 150) - 100 )) ;
			this->addChild(m_SmugglingRoute[i][j][0]) ;

			m_SmugglingRoute[i][j][1] = CSmugglingRoute::create() ;
			m_SmugglingRoute[i][j][1]->setPosition(ccp( j * 200 + 150, visibleSize.height - (i * 150) - 175 )) ;
			this->addChild(m_SmugglingRoute[i][j][1]) ;
		}
	}

	AreaLinked(1, 2) ;//

	scheduleUpdate() ;

	return true ;
}

void CAreaManager::update(float dt)
{
	if(CBuilding::m_bBuyBuilding)
	{
		if(CBuilding::m_bBuyResidential)
		{
			g_pData->m_User.m_nOwnResidential = GetOwnResidentialNumber() ;
		}
		if(CBuilding::m_bBuyRoute)
		{
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<4; j++)
				{
					if(m_SmugglingRoute[i][j][0]->getOwnership())
					{
						AreaLinked(i, j) ;
						AreaLinked(i+1, j) ;
					}
					if(m_SmugglingRoute[i][j][1]->getOwnership())
					{
						AreaLinked(j, i) ;
						AreaLinked(j, i+1) ;
					}
				}
			}
		}

		CBuilding::m_bBuyBuilding = false ;
	}
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

	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			m_SmugglingRoute[i][j][0]->TurnFlow() ;
			m_SmugglingRoute[i][j][1]->TurnFlow() ;
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

	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			m_SmugglingRoute[i][j][0]->RoundFlow() ;
			m_SmugglingRoute[i][j][1]->RoundFlow() ;
		}
	}

	CBuilding::m_bBuyBusiness = false ;
	CBuilding::m_bBuyResidential = false ;
	CBuilding::m_bBuyRoute = false ;
}

void CAreaManager::AreaLinked(int x, int y)
{
	m_Area[y][x]->AreaLinked() ;

	if(x>0)
		m_SmugglingRoute[x-1][y][0]->RouteLinked() ;
	if(x<3)
		m_SmugglingRoute[x][y][0]->RouteLinked() ;

	if(y>0)
		m_SmugglingRoute[y-1][x][1]->RouteLinked() ;
	if(y<3)
		m_SmugglingRoute[y][x][1]->RouteLinked() ;
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
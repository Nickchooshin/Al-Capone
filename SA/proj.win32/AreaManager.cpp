#include "AreaManager.h"
#include "Area.h"
#include "SmugglingRoute.h"

#include "Data.h"
#include "MemberControlPopup.h"

CAreaManager::CAreaManager()
{
}

CAreaManager* CAreaManager::GetInstance()
{
	static CAreaManager AreaManager ;

	return &AreaManager ;
}

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
			m_Area[i][j]->setTag(i*4+j) ;
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
	int i, j ;

	if(CBuilding::m_bBuyBuilding)
	{
		if(CBuilding::m_bBuyResidential)
		{
			g_pData->m_User.m_nOwnResidential = GetOwnResidentialNumber() ;
		}
		if(CBuilding::m_bBuyRoute)
		{
			for(i=0; i<3; i++)
			{
				for(j=0; j<4; j++)
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

	CBuilding::m_bBuyBusiness = false ;
	CBuilding::m_bBuyResidential = false ;
	CBuilding::m_bBuyRoute = false ;
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
}

bool CAreaManager::MoveRouteCheck(CArea *Area)
{
	//
	bool bActivationRoute=false ;
	const int tag = Area->getTag() ;
	const int x = tag%4 ;
	const int y = tag/4 ;

	if(!bActivationRoute && x>0)
	{
		if(m_SmugglingRoute[x-1][y][0]->getOwnership())
		{
			if(!m_Area[y][x-1]->isInspection())
				bActivationRoute = true ;
		}
	}
	if(!bActivationRoute && x<3)
	{
		if(m_SmugglingRoute[x][y][0]->getOwnership())
		{
			if(!m_Area[y][x+1]->isInspection())
				bActivationRoute = true ;
		}
	}

	if(!bActivationRoute && y>0)
	{
		if(m_SmugglingRoute[y-1][x][1]->getOwnership())
		{
			if(!m_Area[y-1][x]->isInspection())
				bActivationRoute = true ;
		}
	}
	if(!bActivationRoute && y<3)
	{
		if(m_SmugglingRoute[y][x][1]->getOwnership())
		{
			if(!m_Area[y+1][x]->isInspection())
				bActivationRoute = true ;
		}
	}

	return bActivationRoute ;
}

void CAreaManager::MoveMemberPrepare(CArea *Area)
{
	const int tag = Area->getTag() ;
	const int x = tag%4 ;
	const int y = tag/4 ;

	MoveEnabled(true) ;

	AreaHighlightOn(x, y) ;
}

void CAreaManager::MoveMemberFinish()
{
	MoveEnabled(false) ;

	AreaHighlightOff() ;
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

void CAreaManager::AreaHighlightOn(int x, int y)
{
	if(x>0)
		RouteHighlight(m_SmugglingRoute[x-1][y][0], m_Area[y][x-1], WAY_LEFT) ;
	if(x<3)
		RouteHighlight(m_SmugglingRoute[x][y][0], m_Area[y][x+1], WAY_RIGHT) ;

	if(y>0)
		RouteHighlight(m_SmugglingRoute[y-1][x][1], m_Area[y-1][x], WAY_UP) ;
	if(y<3)
		RouteHighlight(m_SmugglingRoute[y][x][1], m_Area[y+1][x], WAY_DOWN) ;
}

void CAreaManager::AreaHighlightOff()
{
	int i, j, k ;
	CSmugglingRoute *Route ;

	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			for(k=0; k<2; k++)
			{
				Route = m_SmugglingRoute[i][j][k] ;

				if(Route->isVisible())
				{
					Route->setEnabled(true) ;
					Route->RouteHighlight(false) ;
				}
			}
		}
	}
}

void CAreaManager::MoveEnabled(bool bEnabled)
{
	int i, j, k ;
	bool Enabled = !bEnabled ;
	CArea *Area ;
	CSmugglingRoute *Route ;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			Area = m_Area[i][j] ;

			if(!Area->isInspection())
				Area->setEnabled(Enabled) ;
		}
	}

	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			for(k=0; k<2; k++)
			{
				Route = m_SmugglingRoute[i][j][k] ;

				if(Route->isVisible())
					Route->setEnabled(Enabled) ;
			}
		}
	}
}

void CAreaManager::RouteHighlight(CSmugglingRoute *Route, CArea *Area, ROUTE_WAY Way)
{
	if( Route->getOwnership() && !Area->isInspection() )
	{
		Route->setEnabled(true) ;
		Route->SetRouteWay(Way) ;
		Route->RouteHighlight(true) ;
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
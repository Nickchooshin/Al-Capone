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

	// 배경 화면 초기화
	CCSprite *pBackground = CCSprite::create("Image/Area/All_Background.png") ;
	pBackground->setAnchorPoint(ccp(0, 0)) ;
	this->addChild(pBackground) ;

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

	// 지역 좌표 불러오기
	CCPoint AreaCoord[4][4] ;
	if(!LoadAreaCoord(AreaCoord))
		return false ;

	// 지역 초기화
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			m_Area[i][j] = CArea::create() ;
			//m_Area[i][j]->setPosition(ccp( j * 200 + 150, visibleSize.height - (i * 150) - 100 )) ;
			m_Area[i][j]->setPosition(AreaCoord[i][j]) ;
			m_Area[i][j]->SetBaseInspection(Inspection[i+1][j+1]) ;
			m_Area[i][j]->setTag(i*4+j) ;
			this->addChild(m_Area[i][j]) ;
		}
	}

	// 밀수 가능 지역 초기화
	m_Area[0][0]->SetSmuggling(true) ;
	m_Area[3][3]->SetSmuggling(true) ;

	// 경로 좌표 불러오기
	CCPoint RouteCoord[3][4][2] ;
	if(!LoadRouteCoord(RouteCoord))
		return false ;

	// 경로 초기화
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			m_SmugglingRoute[i][j][0] = CSmugglingRoute::create() ;
			//m_SmugglingRoute[i][j][0]->setPosition(ccp( i * 200 + 250, visibleSize.height - (j * 150) - 100 )) ;
			m_SmugglingRoute[i][j][0]->setPosition(RouteCoord[i][j][0]) ;
			this->addChild(m_SmugglingRoute[i][j][0]) ;

			m_SmugglingRoute[i][j][1] = CSmugglingRoute::create() ;
			//m_SmugglingRoute[i][j][1]->setPosition(ccp( j * 200 + 150, visibleSize.height - (i * 150) - 175 )) ;
			m_SmugglingRoute[i][j][1]->setPosition(RouteCoord[i][j][1]) ;
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

bool CAreaManager::LoadAreaCoord(CCPoint AreaCoord[][4])
{
	int i, j ;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize() ;

	//std::string FilePath = CCFileUtils::sharedFileUtils()->getWritablePath() ;
	//FilePath.append("Data\\AreaCoord.dat") ;
	std::string FilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Data/AreaCoord.dat") ;

	FILE *File = fopen(FilePath.c_str(), "r") ;
	if(File==NULL)	// 파일을 성공적으로 불러오지 못하면, 종료한다
	{
		//
		std::string Message = "Can not find " ;
		Message.append(FilePath) ;

		CCMessageBox(Message.c_str(), "Error");
		CCDirector::sharedDirector()->end() ;
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0) ;
		#endif

		return false ;
	}

	std::string data="" ;
	char key=NULL ;
	bool next=false ;
	bool comment=false ;

	i = j = 0 ;
	while( key!=EOF && (i<4 && j<4) )
	{
		key = fgetc(File) ;

		if(comment)
		{
			if(key==10)
				comment = false ;
		}
		else if(key=='#')
		{
			comment = true ;
		}
		else if(key>='0' && key<='9')
		{
			char temp[2] = {key, NULL} ;
			data.append(temp) ;
		}
		else if(key==',' || (next && data.size()!=0))
		{
			if(!next)
			{
				AreaCoord[i][j].x = atoi(data.c_str()) ;
			}
			else
			{
				AreaCoord[i][j].y = visibleSize.height - atoi(data.c_str()) ;

				j += 1 ;
				i += j/4 ;
				j = j%4 ;
			}

			data.clear() ;
			next = !next ;
		}
	}

	return true ;
}

bool CAreaManager::LoadRouteCoord(CCPoint RouteCoord[][4][2])
{
	int i, j, k=-1 ;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize() ;

	std::string FilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Data/RouteCoord.dat") ;

	FILE *File = fopen(FilePath.c_str(), "r") ;
	if(File==NULL)	// 파일을 성공적으로 불러오지 못하면, 종료한다
	{
		//
		std::string Message = "Can not find " ;
		Message.append(FilePath) ;

		CCMessageBox(Message.c_str(), "Error");
		CCDirector::sharedDirector()->end() ;
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0) ;
		#endif

		return false ;
	}

	std::string data="" ;
	char key=NULL ;
	bool next=false ;
	bool comment=false ;
	bool h=false, v=false ;

	//Horizontally
	//Vertically

	i = j = 0 ;
	while( key!=EOF && !(h && v) )
	{
		key = fgetc(File) ;

		if(comment)
		{
			if(key==10)
				comment = false ;
		}
		else if(key=='#')
		{
			comment = true ;
		}
		else if( k==-1 &&
				 ((key>='a' && key<='z') || (key>='A' && key<='Z')) )
		{
			char temp[2] = {key, NULL} ;
			data.append(temp) ;

			if(data.length()==12 &&
			   (data.compare("Horizontally")==0 || data.compare("horizontally")==0 || data.compare("HORIZONTALLY")==0))
			{
				i = j = 0 ;
				k = 0 ;
				data.clear() ;
			}
			else if(data.length()==10 &&
					(data.compare("Vertically")==0 || data.compare("vertically")==0 || data.compare("VERTICALLY")==0))
			{
				i = j = 0 ;
				k = 1 ;
				data.clear() ;
			}
		}
		else if(k!=-1 &&
				(key>='0' && key<='9'))
		{
			char temp[2] = {key, NULL} ;
			data.append(temp) ;
		}
		else if(k!=-1 &&
				(key==',' || (next && data.size()!=0)))
		{
			if(!next)
			{
				RouteCoord[i][j][k].x = atoi(data.c_str()) ;
			}
			else
			{
				RouteCoord[i][j][k].y = visibleSize.height - atoi(data.c_str()) ;

				j += 1 ;
				i += j/4 ;
				j = j%4 ;

				if(i>=3)
				{
					if(k==0)
						h = true ;
					else
						v = true ;

					k = -1 ;
				}
			}

			data.clear() ;
			next = !next ;
		}
	}
	
	return true ;
}
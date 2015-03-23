#include "Data.h"

#include "cocos2d.h"
#include <stdio.h>
#include <string>
#include "LoadManager.h"

using namespace cocos2d ;

bool CData::init()
{
	std::string FilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Data/Data.dat") ;

	FILE *File = CLoadManager::LoadFile(FilePath.c_str()) ;
	if(File==NULL)
		return false ;

	std::string data="" ;
	char key=NULL ;
	bool next=false ;
	bool comment=false ;
	DATA_TYPE type=NOTHING ;

	while( key!=EOF )
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
		else if(type!=NOTHING)
		{
			if(!next && key=='=')
			{
				next = true ;
			}
			else if(next)
			{
				if(key>='0' && key<='9')
				{
					char temp[2] = {key, NULL} ;
					data.append(temp) ;
				}
				else if(data.size()!=0)
				{
					const int value = atoi(data.c_str()) ;

					switch(type)
					{
					case MAX_CAPACITY :
						m_nMaxCapacity = value ;
						break ;

					case PAY_BUILDING :
						m_nPayBuilding = value ;
						break ;

					case PAY_MEMBER :
						m_nPayMember = value ;
						break ;

					case MAINTENANCE :
						m_nMaintenance = value ;
						break ;

					case PRODUCTION :
						m_nProduction = value ;
						break ;

					case MONEY :
						m_User.m_nMoney = value ;
						break ;

					case STANDBY_MEMBER :
						m_User.m_nStandbyMember = value ;
						break ;
					}

					data.clear() ;
					type = NOTHING ;
					next = false ;
				}
			}
		}
		else if(!next && ((key>='a' && key<='z') || (key>='A' && key<='Z')))
		{
			char temp[2] = {key, NULL} ;
			data.append(temp) ;

			const int length = data.length() ;

			if(length==5 && data.compare("Money")==0)
			{
				type = MONEY ;
				data.clear() ;
			}
			else if(length==9 && data.compare("PayMember")==0)
			{
				type = PAY_MEMBER ;
				data.clear() ;
			}
			else if(length==10 && data.compare("Production")==0)
			{
				type = PRODUCTION ;
				data.clear() ;
			}
			else if(length==11)
			{
				if(data.compare("MaxCapacity")==0)
				{
					type = MAX_CAPACITY ;
					data.clear() ;
				}
				else if(data.compare("PayBuilding")==0)
				{
					type = PAY_BUILDING ;
					data.clear() ;
				}
				else if(data.compare("Maintenance")==0)
				{
					type = MAINTENANCE ;
					data.clear() ;
				}
			}
			else if(length==13 && data.compare("StandbyMember")==0)
			{
				type = STANDBY_MEMBER ;
				data.clear() ;
			}
		}
	}
}
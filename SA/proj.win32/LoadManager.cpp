#include "LoadManager.h"
#include "cocos2d.h"
#include <stdio.h>
#include <string>

using namespace cocos2d ;

FILE* CLoadManager::LoadFile(const char *FilePath)
{
	FILE *File = fopen(FilePath, "r") ;
	
	if(File==NULL)	// 파일을 성공적으로 불러오지 못하면, 종료한다
	{
		std::string Message = "Can not fine " ;
		Message.append(FilePath) ;

		CCMessageBox(Message.c_str(), "Error") ;
		CCDirector::sharedDirector()->end() ;
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0) ;
		#endif

		return NULL ;
	}

	return File ;
}
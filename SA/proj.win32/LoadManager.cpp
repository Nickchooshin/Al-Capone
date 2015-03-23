#include "LoadManager.h"
#include "cocos2d.h"
#include <stdio.h>
#include <string>

using namespace cocos2d ;

FILE* CLoadManager::LoadFile(const char *FilePath)
{
	FILE *File = fopen(FilePath, "r") ;
	
	if(File==NULL)	// ������ ���������� �ҷ����� ���ϸ�, �����Ѵ�
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
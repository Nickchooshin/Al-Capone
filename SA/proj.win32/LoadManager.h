#ifndef __LOAD_MANAGER_H__
#define __LOAD_MANAGER_H__

#include <stdio.h>

class CLoadManager
{
public :
	static FILE* LoadFile(const char *FilePath) ;
} ;

#endif
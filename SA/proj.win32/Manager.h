#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "AreaManager.h"
#include "MemberManager.h"

class CManager
{
public :
	static CAreaManager *Area ;
	static CMemberManager *Member ;
} ;

#endif
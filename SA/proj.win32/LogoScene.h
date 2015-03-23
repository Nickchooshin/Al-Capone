#ifndef __LOGO_SCENE_H__
#define __LOGO_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d ;

class LogoScene : public CCScene
{
public :
	virtual bool init() ;

	static CCScene* scene() ;

	CREATE_FUNC(LogoScene) ;
} ;

#endif
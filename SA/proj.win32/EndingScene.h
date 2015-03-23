#ifndef __ENDING_SCENE_H__
#define __ENDING_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d ;

class EndingScene : public CCScene
{
public :
	virtual bool init() ;

	static CCScene* scene() ;

	CREATE_FUNC(EndingScene) ;
} ;

#endif
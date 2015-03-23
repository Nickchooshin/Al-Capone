#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d ;

class TitleScene : public CCScene
{
public :
	virtual bool init() ;

	static CCScene* scene() ;

	CREATE_FUNC(TitleScene) ;
} ;

#endif
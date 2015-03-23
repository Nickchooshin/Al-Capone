#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d ;

class TutorialScene : public CCScene
{
public :
	virtual bool init() ;

	static CCScene* scene() ;

	CREATE_FUNC(TutorialScene) ;
} ;

#endif
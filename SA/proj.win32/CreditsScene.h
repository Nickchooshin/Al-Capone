#ifndef __CREDITS_SCENE_H__
#define __CREDITS_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CreditsScene : public CCScene
{
public :
	virtual bool init() ;

	static CCScene* scene() ;

	CREATE_FUNC(CreditsScene) ;
} ;

#endif
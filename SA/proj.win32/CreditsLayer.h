#ifndef __CREDITS_LAYER_H__
#define __CREDITS_LAYER_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CreditsLayer : public CCLayer
{
public:
	virtual bool init();  
    
	CREATE_FUNC(CreditsLayer);

	void update(float dt) ;

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) ;
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) ;
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) ;
};

#endif
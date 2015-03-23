#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include "cocos2d.h"

using namespace cocos2d ;

class GameoverLayer : public CCLayer
{
public:
	virtual bool init();  
    
	CREATE_FUNC(GameoverLayer);

	void update(float dt) ;

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) ;
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) ;
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) ;
};

#endif
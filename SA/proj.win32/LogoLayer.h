#ifndef __LOGO_LAYER_H__
#define __LOGO_LAYER_H__

#include "cocos2d.h"

using namespace cocos2d ;

class LogoLayer : public CCLayer
{
private :
	bool m_bCreator ;
	int m_nLogoState ;
	CCSprite *m_pCreator ;
	CCSprite *m_pTeamLogo ;

public:
	virtual bool init();  
    
	CREATE_FUNC(LogoLayer);

	void update(float dt) ;

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) ;
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) ;
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) ;
};

#endif
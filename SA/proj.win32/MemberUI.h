#ifndef __MEMBER_UI_H__
#define __MEMBER_UI_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CMemberUI : public CCNode
{
private :
	CCNode *m_pSprite ;
	CCMenu *m_pMenu ;
	CCLabelTTF *m_pNumberLabel, *m_pPriceLabel ;
	CCLabelTTF *m_pMaxMemberLabel, *m_pUnallocatedMemberLabel ;
	bool m_bVisible ;
	int m_nMemberNum ;

public :
	bool init() ;

	CREATE_FUNC(CMemberUI) ;

	void update(float dt) ;

private :
	void Click_Menu(CCObject *pSender) ;
	void MemberScout(CCObject *pSender) ;
	void NumUpDown(CCObject *pSender) ;

	void SetMenuVisible(bool bVisible) ;
	void SetString() ;
} ;


#endif
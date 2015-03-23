#ifndef __POPUP_MENU_H__
#define __POPUP_MENU_H__

#include "cocos2d.h"

using namespace cocos2d ;

class CPopupMenu
{
public :
	CCMenu *m_pMenu ;

private :
	CPopupMenu() : m_pMenu(NULL) {}
public :
	static CPopupMenu* GetInstance()
	{
		static CPopupMenu PopupMenu ;

		return &PopupMenu ;
	}

	void Release()
	{
		if(m_pMenu!=NULL)
		{
			CCNode *Parent = m_pMenu->getParent() ;
			Parent->removeChild(m_pMenu) ;
			m_pMenu = NULL ;
		}
	}
} ;

#define g_pPopupMenu CPopupMenu::GetInstance()

#endif
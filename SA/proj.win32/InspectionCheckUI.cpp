#include "InspectionCheckUI.h"

#include "Area.h"

bool CInspectionCheckUI::init()
{
	CCMenuItemImage *pIconItem[8] ;

	pIconItem[0] = CCMenuItemImage::create("Image/UI/InspectionCheck/Police_1.png", "Image/UI/InspectionCheck/Police_2.png", this, menu_selector(CInspectionCheckUI::Click_Menu)) ;
	pIconItem[0]->setTag(0) ;

	for(int i=1; i<8; i++)
	{
		char button1[100], button2[100] ;
		sprintf(button1, "Image/UI/InspectionCheck/Num_%d_Button_1.png", i) ;
		sprintf(button2, "Image/UI/InspectionCheck/Num_%d_Button_2.png", i) ;
		pIconItem[i] = CCMenuItemImage::create(button1, button2, this, menu_selector(CInspectionCheckUI::Click_Menu)) ;
		pIconItem[i]->setTag(i) ;
	}

	CCMenu *pMenu = CCMenu::create(pIconItem[0], pIconItem[1], pIconItem[2], pIconItem[3], pIconItem[4], pIconItem[5], pIconItem[6], pIconItem[7], NULL) ;
	pMenu->alignItemsVertically() ;
	pMenu->setPosition(ccp(50, 480)) ;
	this->addChild(pMenu) ;

	return true ;
}

void CInspectionCheckUI::Click_Menu(CCObject *pSender)
{
	CCMenuItem *pItem = (CCMenuItem *)pSender ;
	const int tag = pItem->getTag() ;

	switch(tag)
	{
	case 0 :
		for(int i=1; i<=7; i++)
			CArea::m_bInspectionView[i] = false ;
		break ;

	default :
		for(int i=1; i<=7; i++)
		{
			if(i!=tag)
				CArea::m_bInspectionView[i] = false ;
		}
		CArea::m_bInspectionView[tag] = !CArea::m_bInspectionView[tag] ;
		break ;
	}
}
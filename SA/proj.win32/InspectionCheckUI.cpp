#include "InspectionCheckUI.h"

#include "Area.h"

bool CInspectionCheckUI::init()
{
	CCMenuItemImage *pIconItem[8] ;

	pIconItem[0] = CCMenuItemImage::create("Image/Temp/temp_inspection_all.png", "Image/Temp/temp_inspection_allL.png", this, menu_selector(CInspectionCheckUI::Click_Menu)) ;
	pIconItem[0]->setTag(0) ;

	for(int i=1; i<8; i++)
	{
		pIconItem[i] = CCMenuItemImage::create("Image/Temp/temp_inspection_turn.png", "Image/Temp/temp_inspection_turnL.png", this, menu_selector(CInspectionCheckUI::Click_Menu)) ;
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
	CCMenuItem *Item = (CCMenuItem *)pSender ;
	int tag = Item->getTag() ;

	switch(tag)
	{
	case 0 :
		for(int i=1; i<=7; i++)
			CArea::m_bInspectionView[i] = false ;
		break ;

	default :
		CArea::m_bInspectionView[tag] = !CArea::m_bInspectionView[tag] ;
		break ;
	}
}
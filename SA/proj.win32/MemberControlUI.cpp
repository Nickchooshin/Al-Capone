#include "MemberControlUI.h"

#include "MemberManager.h"

CCScene* CMemberControlUI::scene()
{
	CCScene *scene = CMemberControlUI::create();

	return scene;
}

bool CMemberControlUI::init()
{
	int i, j ;

	CCMenuItemImage *pBackgroundItem = CCMenuItemImage::create("Image/Member/Background.png", "Image/Member/Background.png") ;
	pBackgroundItem->setPosition(ccp(640, 400)) ;
	CCMenu *pBackground = CCMenu::create(pBackgroundItem, NULL) ;
	pBackground->setPosition(ccp(0, 0)) ;
	this->addChild(pBackground, 0) ;

	CCSprite *pListSpace[3] ;
	for(i=0; i<3; i++)
	{
		pListSpace[i] = CCSprite::create("Image/Member/List_Space.png") ;
		pListSpace[i]->setPosition(ccp(640, 590 - (i * 145))) ;
		this->addChild(pListSpace[i], 1) ;
	}

	CCSprite *pMafia[3] ;
	for(i=0; i<3; i++)
	{
		pMafia[i] = CCSprite::create("Image/Member/Mafia_90.png") ;
		pMafia[i]->setPosition(ccp(320, 590 - (i * 145))) ;
		this->addChild(pMafia[i], 2) ;
	}

	CCSprite *pItemSpace[3][3] ;
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			pItemSpace[i][j] = CCSprite::create("Image/Member/Item_Space.png") ;
			pItemSpace[i][j]->setPosition(ccp(440 + (j * 100), 590 - (i * 145))) ;
			this->addChild(pItemSpace[i][j], 2) ;
		}
	}

	CCMenuItemImage *pMoveButton[3] ;
	CCMenuItemImage *pPassButton[3] ;
	CCMenuItemImage *pItemBuyButton[3] ;
	for(i=0; i<3; i++)
	{
		pMoveButton[i] = CCMenuItemImage::create("Image/Member/Move_Button_1.png", "Image/Member/Move_Button_2.png", this, menu_selector(CMemberControlUI::Menu_Click)) ;
		pPassButton[i] = CCMenuItemImage::create("Image/Member/Pass_Button_1.png", "Image/Member/Pass_Button_2.png", this, menu_selector(CMemberControlUI::Menu_Click)) ;
		pItemBuyButton[i] = CCMenuItemImage::create("Image/Member/Item_Buy_Button_1.png", "Image/Member/Item_Buy_Button_2.png", this, menu_selector(CMemberControlUI::Menu_Click)) ;

		pMoveButton[i]->setPosition(ccp(760, 590 - (i * 145))) ;
		pPassButton[i]->setPosition(ccp(pMoveButton[i]->getPosition().x + 100, pMoveButton[i]->getPosition().y)) ;
		pItemBuyButton[i]->setPosition(ccp(pPassButton[i]->getPosition().x + 100, pPassButton[i]->getPosition().y)) ;
	}

	CCMenuItemImage *pCloseButton = CCMenuItemImage::create("Image/Member/Close_Button_1.png", "Image/Member/Close_Button_2.png", this, menu_selector(CMemberControlUI::Menu_Click)) ;
	pCloseButton->setPosition(ccp(934, 182.5)) ;

	CCMenu *pMenu = CCMenu::create(pMoveButton[0], pPassButton[0], pItemBuyButton[0],
								   pMoveButton[1], pPassButton[1], pItemBuyButton[1],
								   pMoveButton[2], pPassButton[2], pItemBuyButton[2],
								   pCloseButton, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pMenu, 2) ;

	return true ;
}

void CMemberControlUI::Menu_Click(CCObject *pSender)
{
	//g_pMemberManager->ShowMenu(false) ;
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->popScene() ;
}
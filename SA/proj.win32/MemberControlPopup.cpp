#include "MemberControlPopup.h"

#include "MemberManager.h"
#include "Member.h"

CMemberControlPopup::CMemberControlPopup()
{
}

CMemberControlPopup* CMemberControlPopup::GetInstance()
{
	static CMemberControlPopup MemberControlPopup ;

	return &MemberControlPopup ;
}

bool CMemberControlPopup::init()
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

		m_pMafia[i] = CCSprite::create("Image/Member/Image_Mafia_90.png") ;
		m_pMafia[i]->setPosition(ccp(320, 590 - (i * 145))) ;
		m_pMafia[i]->setVisible(false) ;
		this->addChild(m_pMafia[i], 2) ;
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

	for(i=0; i<3; i++)
	{
		m_pMoveButton[i] = CCMenuItemImage::create("Image/Member/Move_Button_1.png", "Image/Member/Move_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;
		m_pPassButton[i] = CCMenuItemImage::create("Image/Member/Pass_Button_1.png", "Image/Member/Pass_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;
		m_pItemBuyButton[i] = CCMenuItemImage::create("Image/Member/Item_Buy_Button_1.png", "Image/Member/Item_Buy_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;

		m_pMoveButton[i]->setPosition(ccp(760, 590 - (i * 145))) ;
		m_pPassButton[i]->setPosition(ccp(m_pMoveButton[i]->getPosition().x + 100, m_pMoveButton[i]->getPosition().y)) ;
		m_pItemBuyButton[i]->setPosition(ccp(m_pPassButton[i]->getPosition().x + 100, m_pPassButton[i]->getPosition().y)) ;
	}

	CCMenuItemImage *pCloseButton = CCMenuItemImage::create("Image/Member/Close_Button_1.png", "Image/Member/Close_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;
	pCloseButton->setPosition(ccp(934, 182.5)) ;

	CCMenu *pMenu = CCMenu::create(m_pMoveButton[0], m_pPassButton[0], m_pItemBuyButton[0],
								   m_pMoveButton[1], m_pPassButton[1], m_pItemBuyButton[1],
								   m_pMoveButton[2], m_pPassButton[2], m_pItemBuyButton[2],
								   pCloseButton, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pMenu, 2) ;

	return true ;
}

void CMemberControlPopup::SetMemberData(std::vector<CMember> &Member)
{
	int i ;
	int num = Member.size() ;

	for(i=0; i<3; i++)
	{
		m_pMafia[i]->setVisible(false) ;
		m_pMoveButton[i]->setEnabled(false) ;
		m_pPassButton[i]->setEnabled(false) ;
		m_pItemBuyButton[i]->setEnabled(false) ;
	}

	for(i=0; i<num; i++)
	{
		m_pMafia[i]->setVisible(true) ;
		m_pMoveButton[i]->setEnabled(true) ;
		m_pPassButton[i]->setEnabled(true) ;
		m_pItemBuyButton[i]->setEnabled(true) ;
	}
}

void CMemberControlPopup::Menu_Click(CCObject *pSender)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->popScene() ;
}
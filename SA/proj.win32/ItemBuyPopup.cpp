#include "ItemBuyPopup.h"

#include "Member.h"
#include "MemberControlPopup.h"

CItemBuyPopup::CItemBuyPopup()
{
}

CItemBuyPopup* CItemBuyPopup::GetInstance()
{
	static CItemBuyPopup ItemBuyPopup ;

	return &ItemBuyPopup ;
}

bool CItemBuyPopup::init()
{
	int i, j ;

	m_pMember = NULL ;

	// 배경
	CCSprite *pBackground = CCSprite::create("Image/UI/BuyMenu/B_BackGround_2.png") ;
	pBackground->setPosition(ccp(640, 400)) ;
	this->addChild(pBackground, 0) ;

	// 아이템 슬롯
	CCSprite *pItemSlot = CCSprite::create("Image/UI/BuyMenu/B_Item_Slot.png") ;
	pItemSlot->setPosition(ccp(325, 445)) ;
	this->addChild(pItemSlot, 1) ;

	CCSprite *pCharSpace = CCSprite::create("Image/UI/BuyMenu/Charactor_Space.png") ;
	pCharSpace->setPosition(ccp(325, 590)) ;
	this->addChild(pCharSpace, 2) ;

	CCSprite *pItemSpace1[3] ;
	for(i=0; i<3; i++)
	{
		pItemSpace1[i] = CCSprite::create("Image/UI/BuyMenu/Item_Space.png") ;
		pItemSpace1[i]->setPosition(ccp(325, 490 - (i * 95))) ;
		this->addChild(pItemSpace1[i], 2) ;

		m_pItem[i] = CCMenuItemImage::create("", "", this, menu_selector(CItemBuyPopup::Menu_Click)) ;
		m_pItem[i]->setPosition(pItemSpace1[i]->getPosition()) ; 
		m_pItem[i]->setVisible(false) ;
		m_pItem[i]->setTag(i) ;
	}

	CCMenu *pItemMenu = CCMenu::create(m_pItem[0], m_pItem[1], m_pItem[2], NULL) ;
	pItemMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pItemMenu, 3) ;

	CCSprite *pMan = CCSprite::create("Image/UI/BuyMenu/Man_1.png") ;
	pMan->setPosition(ccp(325, 590)) ;
	this->addChild(pMan, 3) ;

	// 구매 버튼
	CCMenuItemImage *pBuyButton[3] ;
	CCSprite *pItemSpace2[3] ;
	CCSprite *pName[3] ;
	CCSprite *pExplanation[3] ;
	CCSprite *pNumerical1[3][3], *pNumerical2[3][3] ;

	for(i=0; i<3; i++)
	{
		pBuyButton[i] = CCMenuItemImage::create("Image/UI/BuyMenu/B_Buy_Button.png", "Image/UI/BuyMenu/B_Buy_Button.png", this, menu_selector(CItemBuyPopup::Menu_Click)) ;
		pBuyButton[i]->setPosition(ccp(710, 590 - (i * 145))) ;
		pBuyButton[i]->setTag(i+3) ;

		pItemSpace2[i] = CCSprite::create("Image/UI/BuyMenu/Item_Space.png") ;
		pItemSpace2[i]->setPosition(ccp(470, 590 - (i * 145))) ;
		this->addChild(pItemSpace2[i], 2) ;

		pName[i] = CCSprite::create("Image/UI/BuyMenu/B_Name.png") ;
		pName[i]->setPosition(ccp(570, 620 - (i * 145))) ;
		this->addChild(pName[i], 2) ;

		pExplanation[i] = CCSprite::create("Image/UI/BuyMenu/B_Explanation.png") ;
		pExplanation[i]->setPosition(ccp(670, 571 - (i * 145))) ;
		this->addChild(pExplanation[i], 2) ;

		for(j=0; j<3; j++)
		{
			pNumerical1[i][j] = CCSprite::create("Image/UI/BuyMenu/B_Numerical_1.png") ;
			pNumerical1[i][j]->setPosition(ccp(875.5, 620 - (i * 145) - (j * 30))) ;
			this->addChild(pNumerical1[i][j], 2) ;

			pNumerical2[i][j] = CCSprite::create("Image/UI/BuyMenu/B_Numerical_2.png") ;
			pNumerical2[i][j]->setPosition(ccp(965, 620 - (i * 145) - (j * 30))) ;
			this->addChild(pNumerical2[i][j], 2) ;
		}
	}

	CCMenu *pBuyMenu = CCMenu::create(pBuyButton[0], pBuyButton[1], pBuyButton[2], NULL) ;
	pBuyMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pBuyMenu, 1) ;

	CCSprite *pAcohol = CCSprite::create("Image/UI/BuyMenu/Acohol_Icon.png") ;
	pAcohol->setPosition(ccp(470, 590)) ;
	this->addChild(pAcohol, 3) ;

	CCSprite *pOriginalDrink = CCSprite::create("Image/UI/BuyMenu/Original_Drink_Icon.png") ;
	pOriginalDrink->setPosition(ccp(470, 445)) ;
	this->addChild(pOriginalDrink, 3) ;

	CCSprite *pNarcotic = CCSprite::create("Image/UI/BuyMenu/Narcotic_Icon.png") ;
	pNarcotic->setPosition(ccp(470, 300)) ;
	this->addChild(pNarcotic, 3) ;

	// 확인, 취소
	CCMenuItemImage *pCheck ;
	pCheck = CCMenuItemImage::create("Image/UI/BuyMenu/B_Check_1.png", "Image/UI/BuyMenu/B_Check_2.png", this, menu_selector(CItemBuyPopup::Menu_Click)) ;
	pCheck->setPosition(ccp(704, 183)) ;
	pCheck->setTag(6) ;

	CCMenuItemImage *pCancel ;
	pCancel = CCMenuItemImage::create("Image/UI/BuyMenu/B_Cancel_1.png", "Image/UI/BuyMenu/B_Cancel_2.png", this, menu_selector(CItemBuyPopup::Menu_Click)) ;
	pCancel->setPosition(ccp(914, 183)) ;
	pCancel->setTag(7) ;

	CCMenu *pFinalMenu = CCMenu::create(pCheck, pCancel, NULL) ;
	pFinalMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pFinalMenu, 3) ;

	// 가격
	CCSprite *pCostSpace = CCSprite::create("Image/UI/BuyMenu/B_Cost_Space.png") ;
	pCostSpace->setPosition(ccp(325, 183)) ;
	this->addChild(pCostSpace, 1) ;

	return true ;
}

void CItemBuyPopup::SetMemberData(CMember *pMember)
{
	m_pMember = pMember ;

	m_ItemList.clear() ;

	for(int i=0; i<3; i++)
	{
		if(m_pMember->m_ItemList[i]!=CMember::NOTHING)
			m_ItemList.push_back(m_pMember->m_ItemList[i]) ;
		else
			break ;
	}

	UpdateItemList() ;
}

void CItemBuyPopup::SetItemList()
{
	int i ;
	int n = m_ItemList.size() ;

	for(i=0; i<n; i++)
		m_pMember->m_ItemList[i] = (CMember::ITEM_TYPE)m_ItemList[i] ;

	for(i=n; i<3; i++)
		m_pMember->m_ItemList[i] = CMember::NOTHING ;
}

bool CItemBuyPopup::AddItem(int type)
{
	if(m_ItemList.size()==3)
		return false ;

	m_ItemList.push_back(type) ;

	return true ;
}

void CItemBuyPopup::UpdateItemList()
{
	int i ;
	int n = m_ItemList.size() ;

	for(i=0; i<n; i++)
	{
		switch(m_ItemList[i])
		{
		case CMember::ACOHOL :
			m_pItem[i]->setVisible(true) ;
			m_pItem[i]->setNormalImage(CCSprite::create("Image/UI/BuyMenu/Acohol_Icon.png")) ;
			m_pItem[i]->setSelectedImage(CCSprite::create("Image/UI/BuyMenu/Acohol_Icon.png")) ;
			break ;

		case CMember::ORIGINAL_DRINK :
			m_pItem[i]->setVisible(true) ;
			m_pItem[i]->setNormalImage(CCSprite::create("Image/UI/BuyMenu/Original_Drink_Icon.png")) ;
			m_pItem[i]->setSelectedImage(CCSprite::create("Image/UI/BuyMenu/Original_Drink_Icon.png")) ;
			break ;

		case CMember::NARCOTIC :
			m_pItem[i]->setVisible(true) ;
			m_pItem[i]->setNormalImage(CCSprite::create("Image/UI/BuyMenu/Narcotic_Icon.png")) ;
			m_pItem[i]->setSelectedImage(CCSprite::create("Image/UI/BuyMenu/Narcotic_Icon.png")) ;
			break ;
		}
	}

	for(i=n; i<3; i++)
	{
		m_pItem[i]->setVisible(false) ;
	}
}

void CItemBuyPopup::Menu_Click(CCObject *pSender)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	CCMenuItem *pItem = (CCMenuItem *)pSender ;
	const int tag = pItem->getTag() ;
	const int index = tag%3 ;

	switch(tag)
	{
	case 0 :
	case 1 :
	case 2 :
		m_ItemList.erase(m_ItemList.begin() + index) ;
		UpdateItemList() ;
		break ;

	case 3 :
	case 4 :
	case 5 :
		AddItem(index+1) ;
		UpdateItemList() ;
		break ;

	case 6 :
		SetItemList() ;
		g_pMemberControlPopup->UpdateItemList() ;
		pDirector->popScene() ;
		pDirector->pushScene(g_pMemberControlPopup) ;
		break ;

	case 7 :
		pDirector->popScene() ;
		pDirector->pushScene(g_pMemberControlPopup) ;
		break ;
	}
}
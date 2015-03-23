#include "ItemBuyPopup.h"

#include "Member.h"
#include "MemberControlPopup.h"

#include "Data.h"

#include "SimpleAudioEngine.h"

CItemBuyPopup::CItemBuyPopup()
{
}

CItemBuyPopup* CItemBuyPopup::GetInstance()
{
	static CItemBuyPopup Instance ;

	return &Instance ;
}

bool CItemBuyPopup::init()
{
	int i, j ;

	m_pMember = NULL ;

	// 배경
	CCSprite *pBackground = CCSprite::create("Image/Game/UI/BuyMenu/B_BackGround_2.png") ;
	pBackground->setPosition(ccp(640, 400)) ;
	this->addChild(pBackground, 0) ;

	// 아이템 슬롯
	CCSprite *pItemSlot = CCSprite::create("Image/Game/UI/BuyMenu/B_Item_Slot.png") ;
	pItemSlot->setPosition(ccp(325, 445)) ;
	this->addChild(pItemSlot, 1) ;

	CCSprite *pCharSpace = CCSprite::create("Image/Game/Member/Charactor_Space.png") ;
	pCharSpace->setPosition(ccp(325, 590)) ;
	this->addChild(pCharSpace, 2) ;

	CCSprite *pItemSpace1[3] ;
	for(i=0; i<3; i++)
	{
		pItemSpace1[i] = CCSprite::create("Image/Game/UI/BuyMenu/Item_Space.png") ;
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

	CCSprite *pMan = CCSprite::create("Image/Game/Member/Man_1.png") ;
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
		pBuyButton[i] = CCMenuItemImage::create("Image/Game/UI/BuyMenu/B_Buy_Button.png", "Image/Game/UI/BuyMenu/B_Buy_Button.png", this, menu_selector(CItemBuyPopup::Menu_Click)) ;
		pBuyButton[i]->setPosition(ccp(710, 590 - (i * 145))) ;
		pBuyButton[i]->setTag(i+3) ;

		pItemSpace2[i] = CCSprite::create("Image/Game/UI/BuyMenu/Item_Space.png") ;
		pItemSpace2[i]->setPosition(ccp(470, 590 - (i * 145))) ;
		this->addChild(pItemSpace2[i], 2) ;

		pName[i] = CCSprite::create("Image/Game/UI/BuyMenu/B_Name.png") ;
		pName[i]->setPosition(ccp(570, 620 - (i * 145))) ;
		this->addChild(pName[i], 2) ;

		pExplanation[i] = CCSprite::create("Image/Game/UI/BuyMenu/B_Explanation.png") ;
		pExplanation[i]->setPosition(ccp(670, 571 - (i * 145))) ;
		this->addChild(pExplanation[i], 2) ;

		for(j=0; j<3; j++)
		{
			pNumerical1[i][j] = CCSprite::create("Image/Game/UI/BuyMenu/B_Numerical_1.png") ;
			pNumerical1[i][j]->setPosition(ccp(875.5, 620 - (i * 145) - (j * 30))) ;
			this->addChild(pNumerical1[i][j], 2) ;

			pNumerical2[i][j] = CCSprite::create("Image/Game/UI/BuyMenu/B_Numerical_2.png") ;
			pNumerical2[i][j]->setPosition(ccp(965, 620 - (i * 145) - (j * 30))) ;
			this->addChild(pNumerical2[i][j], 2) ;
		}
	}

	CCMenu *pBuyMenu = CCMenu::create(pBuyButton[0], pBuyButton[1], pBuyButton[2], NULL) ;
	pBuyMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pBuyMenu, 1) ;

	CCSprite *pAcohol = CCSprite::create("Image/Game/UI/BuyMenu/Acohol_Icon.png") ;
	pAcohol->setPosition(ccp(470, 590)) ;
	this->addChild(pAcohol, 3) ;

	CCSprite *pOriginalDrink = CCSprite::create("Image/Game/UI/BuyMenu/Original_Drink_Icon.png") ;
	pOriginalDrink->setPosition(ccp(470, 445)) ;
	this->addChild(pOriginalDrink, 3) ;

	CCSprite *pNarcotic = CCSprite::create("Image/Game/UI/BuyMenu/Narcotic_Icon.png") ;
	pNarcotic->setPosition(ccp(470, 300)) ;
	this->addChild(pNarcotic, 3) ;

	//
	CCLabelTTF *pLName[3] ;
	CCLabelTTF *pLExplanation[3] ;
	CCLabelTTF *pLBuy[3][2] ;
	CCLabelTTF *pLSell[3][2] ;
	CCLabelTTF *pLAttention[3][2] ;
	for(i=0; i<3; i++)
	{
		char str[1024] ;
		WCHAR wstr[1024] ;

		sprintf(str, g_pData->m_Item.m_sName[i].c_str()) ;
		MultiByteToWideChar( CP_ACP, 0, str, -1, wstr, 1024 ) ;
		WideCharToMultiByte( CP_UTF8, 0, wstr, -1, str, 1024, NULL, NULL ) ;
		pLName[i] = CCLabelTTF::create(str, "fonts/arial.ttf", 18, pName[i]->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
		pLName[i]->setColor(ccc3(0, 0, 0)) ;
		pLName[i]->setPosition(pName[i]->getPosition()) ;
		this->addChild(pLName[i], 3) ;

		sprintf(str, g_pData->m_Item.m_sExplanation[i].c_str()) ;
		MultiByteToWideChar( CP_ACP, 0, str, -1, wstr, 1024 ) ;
		WideCharToMultiByte( CP_UTF8, 0, wstr, -1, str, 1024, NULL, NULL ) ;
		pLExplanation[i] = CCLabelTTF::create(str, "fonts/arial.ttf", 18, CCSize(pExplanation[i]->getContentSize().width-12, pExplanation[i]->getContentSize().height-6), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop) ;
		pLExplanation[i]->setColor(ccc3(0, 0, 0)) ;
		pLExplanation[i]->setPosition(pExplanation[i]->getPosition()) ;
		this->addChild(pLExplanation[i], 3) ;

		sprintf(str, "구매가격") ;
		MultiByteToWideChar( CP_ACP, 0, str, -1, wstr, 1024 ) ;
		WideCharToMultiByte( CP_UTF8, 0, wstr, -1, str, 1024, NULL, NULL ) ;
		pLBuy[i][0] = CCLabelTTF::create(str, "fonts/arial.ttf", 18, pNumerical1[i][0]->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
		pLBuy[i][0]->setColor(ccc3(0, 0, 0)) ;
		pLBuy[i][0]->setPosition(pNumerical1[i][0]->getPosition()) ;
		this->addChild(pLBuy[i][0], 3) ;

		sprintf(str, "%d", g_pData->m_Item.m_nBuy[i]) ;
		pLBuy[i][1] = CCLabelTTF::create(str, "fonts/arial.ttf", 18, pNumerical2[i][0]->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
		pLBuy[i][1]->setColor(ccc3(0, 0, 0)) ;
		pLBuy[i][1]->setPosition(pNumerical2[i][0]->getPosition()) ;
		this->addChild(pLBuy[i][1], 3) ;

		sprintf(str, "판매가격") ;
		MultiByteToWideChar( CP_ACP, 0, str, -1, wstr, 1024 ) ;
		WideCharToMultiByte( CP_UTF8, 0, wstr, -1, str, 1024, NULL, NULL ) ;
		pLSell[i][0] = CCLabelTTF::create(str, "fonts/arial.ttf", 18, pNumerical1[i][1]->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
		pLSell[i][0]->setColor(ccc3(0, 0, 0)) ;
		pLSell[i][0]->setPosition(pNumerical1[i][1]->getPosition()) ;
		this->addChild(pLSell[i][0], 3) ;

		sprintf(str, "%d", g_pData->m_Item.m_nSell[i]) ;
		pLSell[i][1] = CCLabelTTF::create(str, "fonts/arial.ttf", 18, pNumerical2[i][1]->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
		pLSell[i][1]->setColor(ccc3(0, 0, 0)) ;
		pLSell[i][1]->setPosition(pNumerical2[i][1]->getPosition()) ;
		this->addChild(pLSell[i][1], 3) ;

		sprintf(str, "주목도") ;
		MultiByteToWideChar( CP_ACP, 0, str, -1, wstr, 1024 ) ;
		WideCharToMultiByte( CP_UTF8, 0, wstr, -1, str, 1024, NULL, NULL ) ;
		pLAttention[i][0] = CCLabelTTF::create(str, "fonts/arial.ttf", 18, pNumerical1[i][2]->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
		pLAttention[i][0]->setColor(ccc3(0, 0, 0)) ;
		pLAttention[i][0]->setPosition(pNumerical1[i][2]->getPosition()) ;
		this->addChild(pLAttention[i][0], 3) ;

		sprintf(str, "%d", g_pData->m_Item.m_nAttention[i]) ;
		pLAttention[i][1] = CCLabelTTF::create(str, "fonts/arial.ttf", 18, pNumerical2[i][2]->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
		pLAttention[i][1]->setColor(ccc3(0, 0, 0)) ;
		pLAttention[i][1]->setPosition(pNumerical2[i][2]->getPosition()) ;
		this->addChild(pLAttention[i][1], 3) ;
	}
	//

	// 확인, 취소
	CCMenuItemImage *pCheck ;
	pCheck = CCMenuItemImage::create("Image/Game/UI/BuyMenu/B_Check_1.png", "Image/Game/UI/BuyMenu/B_Check_2.png", this, menu_selector(CItemBuyPopup::Menu_Click)) ;
	pCheck->setPosition(ccp(704, 183)) ;
	pCheck->setTag(6) ;

	CCMenuItemImage *pCancel ;
	pCancel = CCMenuItemImage::create("Image/Game/UI/BuyMenu/B_Cancel_1.png", "Image/Game/UI/BuyMenu/B_Cancel_2.png", this, menu_selector(CItemBuyPopup::Menu_Click)) ;
	pCancel->setPosition(ccp(914, 183)) ;
	pCancel->setTag(7) ;

	CCMenu *pFinalMenu = CCMenu::create(pCheck, pCancel, NULL) ;
	pFinalMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pFinalMenu, 3) ;

	// 가격
	CCSprite *pCostSpace = CCSprite::create("Image/Game/UI/BuyMenu/B_Cost_Space.png") ;
	pCostSpace->setPosition(ccp(325, 183)) ;
	this->addChild(pCostSpace, 1) ;

	m_pPriceLabel = CCLabelTTF::create("0", "fonts/arial.ttf", 30, pCostSpace->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
	m_pPriceLabel->setColor(ccc3(0, 0, 0)) ;
	m_pPriceLabel->setPosition(pCostSpace->getPosition()) ;
	this->addChild(m_pPriceLabel, 2) ;

	return true ;
}

void CItemBuyPopup::SetMemberData(CMember *pMember, int Index)
{
	m_pMember = pMember ;
	m_nMemberIndex = Index ;

	m_nTotalPrice = 0 ;

	m_ItemList.clear() ;

	for(int i=0; i<3; i++)
	{
		if(m_pMember->m_ItemList[i]!=NOTHING)
			m_ItemList.push_back(m_pMember->m_ItemList[i]) ;
		else
			break ;
	}

	UpdateItemList() ;
	UpdateItemPrice() ;
}

void CItemBuyPopup::SetItemList()
{
	int i ;
	int n = m_ItemList.size() ;

	for(i=0; i<n; i++)
		m_pMember->m_ItemList[i] = (ITEM_TYPE)m_ItemList[i] ;

	for(i=n; i<3; i++)
		m_pMember->m_ItemList[i] = NOTHING ;
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
		case ACOHOL :
			m_pItem[i]->setVisible(true) ;
			m_pItem[i]->setNormalImage(CCSprite::create("Image/Game/UI/BuyMenu/Acohol_Icon.png")) ;
			m_pItem[i]->setSelectedImage(CCSprite::create("Image/Game/UI/BuyMenu/Acohol_Icon.png")) ;
			break ;

		case ORIGINAL_DRINK :
			m_pItem[i]->setVisible(true) ;
			m_pItem[i]->setNormalImage(CCSprite::create("Image/Game/UI/BuyMenu/Original_Drink_Icon.png")) ;
			m_pItem[i]->setSelectedImage(CCSprite::create("Image/Game/UI/BuyMenu/Original_Drink_Icon.png")) ;
			break ;

		case NARCOTIC :
			m_pItem[i]->setVisible(true) ;
			m_pItem[i]->setNormalImage(CCSprite::create("Image/Game/UI/BuyMenu/Narcotic_Icon.png")) ;
			m_pItem[i]->setSelectedImage(CCSprite::create("Image/Game/UI/BuyMenu/Narcotic_Icon.png")) ;
			break ;
		}
	}

	for(i=n; i<3; i++)
	{
		m_pItem[i]->setVisible(false) ;
	}
}

void CItemBuyPopup::UpdateItemPrice(int Price)
{
	char str[100] ;

	m_nTotalPrice += Price ;

	sprintf(str, "%d", m_nTotalPrice) ;
	m_pPriceLabel->setString(str) ;
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
		UpdateItemPrice( - ( g_pData->m_Item.m_nBuy[m_ItemList[index]] ) ) ;
		m_ItemList.erase(m_ItemList.begin() + index) ;
		UpdateItemList() ;
		break ;

	case 3 :
	case 4 :
	case 5 :
		if(AddItem(index))
		{
			UpdateItemList() ;
			UpdateItemPrice(g_pData->m_Item.m_nBuy[index]) ;
		}
		break ;

	case 6 :
		if(g_pData->m_User.m_nMoney >= m_nTotalPrice)
		{
			g_pData->m_User.m_nMoney -= m_nTotalPrice ;

			m_pMember->setBuy(true) ;
			SetItemList() ;
			g_pMemberControlPopup->UpdateItemList() ;
			g_pMemberControlPopup->SetAllButtonEnabled(m_nMemberIndex, false) ;

			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Buy_3.wav") ;

			pDirector->popScene() ;
			CCDelayTime::create(0.1f);
			pDirector->pushScene(g_pMemberControlPopup) ;
		}
		break ;

	case 7 :
		pDirector->popScene() ;
		pDirector->pushScene(g_pMemberControlPopup) ;
		break ;
	}
}
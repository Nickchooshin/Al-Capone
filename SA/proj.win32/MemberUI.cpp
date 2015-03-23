#include "MemberUI.h"
#include "Data.h"

bool CMemberUI::init()
{
	m_bVisible = false ;
	m_nMemberNum = 0 ;

	CCSprite *pFrame1 = CCSprite::create("Image/UI/Space.png") ;
	pFrame1->setPosition(ccp(110, 40)) ;
	this->addChild(pFrame1, 0) ;

	CCSprite *pFrame2 = CCSprite::create("Image/UI/Space.png") ;
	pFrame2->setPosition(ccp(320, 40)) ;
	this->addChild(pFrame2, 0) ;

	CCSprite *pIcon1 = CCSprite::create("Image/UI/Icon_1.png") ;
	pIcon1->setPosition(ccp(40, 40)) ;
	this->addChild(pIcon1, 0) ;

	CCSprite *pIcon2 = CCSprite::create("Image/UI/Icon_2.png") ;
	pIcon2->setPosition(ccp(250, 40)) ;
	this->addChild(pIcon2, 0) ;

	// Label
	m_pMaxMemberLabel = CCLabelTTF::create("", "fonts/arial.ttf", 30, CCSize(135, 50), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter) ;
	m_pMaxMemberLabel->setColor(ccc3(0, 0, 0)) ;
	m_pMaxMemberLabel->setPosition(ccp(137.5, 40)) ;
	this->addChild(m_pMaxMemberLabel, 1) ;

	m_pUnallocatedMemberLabel = CCLabelTTF::create("", "fonts/arial.ttf", 30, CCSize(135, 50), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter) ;
	m_pUnallocatedMemberLabel->setColor(ccc3(0, 0, 0)) ;
	m_pUnallocatedMemberLabel->setPosition(ccp(347, 40)) ;
	this->addChild(m_pUnallocatedMemberLabel, 1) ;



	CCMenuItemImage *pMemberMenu = CCMenuItemImage::create("Image/UI/Man_Buy.png", "Image/UI/Man_Buy.png", this, menu_selector(CMemberUI::Click_Menu)) ;
	pMemberMenu->setPosition(ccp(760, 40)) ;

	CCMenu *pMenu = CCMenu::create(pMemberMenu, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pMenu, 0) ;

	// Sprite
	CCMenuItemImage *pBackgroundItem = CCMenuItemImage::create("Image/UI/ManMenu/Background.png", "Image/UI/ManMenu/Background.png") ;
	pBackgroundItem->setPosition(ccp(760, 210)) ;
	CCMenu *pBackground = CCMenu::create(pBackgroundItem, NULL) ;
	pBackground->setPosition(ccp(0, 0)) ;

	CCSprite *pManSpace = CCSprite::create("Image/UI/ManMenu/Charactor_Space.png") ;
	pManSpace->setPosition(ccp(725, 242.5)) ;

	CCSprite *pMan = CCSprite::create("Image/UI/ManMenu/Man_1.png") ;
	pMan->setPosition(pManSpace->getPosition()) ;

	CCSprite *pNumberSpace = CCSprite::create("Image/UI/ManMenu/Number_Space.png") ;
	pNumberSpace->setPosition(ccp(840, 242.5)) ;

	m_pSprite = CCNode::create() ;
	m_pSprite->addChild(pBackground) ;
	m_pSprite->addChild(pManSpace) ;
	m_pSprite->addChild(pMan) ;
	m_pSprite->addChild(pNumberSpace) ;
	this->addChild(m_pSprite, 1) ;

	// Menu
	CCMenuItemImage *pBuyButton = CCMenuItemImage::create("Image/UI/ManMenu/Buy_Button_1.png", "Image/UI/ManMenu/Buy_Button_2.png", this, menu_selector(CMemberUI::MemberScout)) ;
	pBuyButton->setPosition(ccp(725, 127.5)) ;

	CCMenuItemImage *pUpButton = CCMenuItemImage::create("Image/UI/ManMenu/Up_Button_1.png", "Image/UI/ManMenu/Up_Button_2.png", this, menu_selector(CMemberUI::NumUpDown)) ;
	pUpButton->setPosition(ccp(840, 300)) ;
	pUpButton->setTag(0) ;

	CCMenuItemImage *pDownButton = CCMenuItemImage::create("Image/UI/ManMenu/Down_Button_1.png", "Image/UI/ManMenu/Down_Button_2.png", this, menu_selector(CMemberUI::NumUpDown)) ;
	pDownButton->setPosition(ccp(840, 185)) ;
	pDownButton->setTag(1) ;

	m_pMenu = CCMenu::create(pBuyButton, pUpButton, pDownButton, NULL) ;
	m_pMenu->setPosition(ccp(0, 0)) ;
	this->addChild(m_pMenu, 2) ;

	// Label
	m_pNumberLabel = CCLabelTTF::create("", "fonts/arial.ttf", 25, pNumberSpace->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
	m_pNumberLabel->setColor(ccc3(0, 0, 0)) ;
	m_pNumberLabel->setPosition(pNumberSpace->getPosition()) ;
	this->addChild(m_pNumberLabel, 3) ;

	m_pPriceLabel = CCLabelTTF::create("", "fonts/arial.ttf", 25, pBuyButton->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
	m_pPriceLabel->setColor(ccc3(255, 255, 0)) ;
	m_pPriceLabel->setPosition(pBuyButton->getPosition()) ;
	this->addChild(m_pPriceLabel, 3) ;

	SetMenuVisible(m_bVisible) ;

	this->scheduleUpdate() ;

	return true ;
}

void CMemberUI::Click_Menu(CCObject *pSender)
{
	m_bVisible = !m_bVisible ;

	m_nMemberNum = 0 ;
	SetMenuVisible(m_bVisible) ;
	SetString() ;
}

void CMemberUI::MemberScout(CCObject *pSender)
{
	if((g_pData->m_User.m_nMoney >= m_nMemberNum * g_pData->m_nPayMember) && 
		((g_pData->m_User.m_nOwnResidential * g_pData->m_nMaxCapacity) - g_pData->m_User.m_nHaveMember >= m_nMemberNum))
	{
		g_pData->m_User.m_nMoney -= m_nMemberNum * g_pData->m_nPayMember ;
		g_pData->m_User.m_nHaveMember += m_nMemberNum ;
		g_pData->m_User.m_nStandbyMember += m_nMemberNum ;

		Click_Menu(NULL) ;
	}
}

void CMemberUI::NumUpDown(CCObject *pSender)
{
	CCMenuItem *pMenuItem = (CCMenuItem*)pSender ;
	int tag = pMenuItem->getTag() ;

	switch(tag)
	{
	case 0 :
		m_nMemberNum += 1 ;
		break ;

	case 1 :
		m_nMemberNum -= 1 ;
		break ;
	}

	if(m_nMemberNum<0)
		m_nMemberNum = 0 ;
	if(m_nMemberNum>g_pData->m_User.m_nOwnResidential * g_pData->m_nMaxCapacity)
		m_nMemberNum = g_pData->m_User.m_nOwnResidential * g_pData->m_nMaxCapacity ;

	SetString() ;
}

void CMemberUI::update(float dt)
{
	char str[1024] ;

	sprintf(str, "%d / %d", g_pData->m_User.m_nHaveMember, g_pData->m_User.m_nOwnResidential * g_pData->m_nMaxCapacity) ;
	m_pMaxMemberLabel->setString(str) ;	// 현재/최대

	sprintf(str, "%d", g_pData->m_User.m_nStandbyMember) ;
	m_pUnallocatedMemberLabel->setString(str) ;	// 대기
}

void CMemberUI::SetMenuVisible(bool bVisible)
{
	m_pSprite->setVisible(bVisible) ;
	m_pMenu->setVisible(bVisible) ;
	m_pNumberLabel->setVisible(bVisible) ;
	m_pPriceLabel->setVisible(bVisible) ;
}

void CMemberUI::SetString()
{
	char str[1024] ;

	sprintf(str, "%d", m_nMemberNum) ;
	m_pNumberLabel->setString(str) ;

	WCHAR wstr[1024] ;
	sprintf(str, "구입 : %2d", m_nMemberNum) ;
	MultiByteToWideChar( CP_ACP, 0, str, -1, wstr, 1024 ) ;
	WideCharToMultiByte( CP_UTF8, 0, wstr, -1, str, 1024, NULL, NULL ) ;
	m_pPriceLabel->setString(str) ;
}
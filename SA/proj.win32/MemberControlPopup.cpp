#include "MemberControlPopup.h"

#include "MemberManager.h"
#include "MemberIcon.h"
#include "Area.h"
#include "AreaManager.h"
#include "ItemBuyPopup.h"

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

	m_pMemberIcon = NULL ;
	m_bPassItem = false ;

	// ��׶���
	CCSprite *pBackground = CCSprite::create("Image/Member/C_Background.png") ;
	pBackground->setPosition(ccp(640, 400)) ;
	this->addChild(pBackground, 0) ;

	CCSprite *pListSpace[3] ;
	for(i=0; i<3; i++)
	{
		pListSpace[i] = CCSprite::create("Image/Member/List_Space_1.png") ;
		pListSpace[i]->setPosition(ccp(640, 590 - (i * 145))) ;
		this->addChild(pListSpace[i], 1) ;
	}

	// ���Ǿ� �ʻ�ȭ
	CCSprite *pMafia[3] ;
	for(i=0; i<3; i++)
	{
		pMafia[i] = CCSprite::create("Image/Member/Charactor_Space.png") ;
		pMafia[i]->setPosition(ccp(320, 590 - (i * 145))) ;
		this->addChild(pMafia[i], 2) ;

		m_pMafia[i] = CCSprite::create("Image/Member/Man_1.png") ;
		m_pMafia[i]->setPosition(ccp(320, 590 - (i * 145))) ;
		m_pMafia[i]->setVisible(false) ;
		this->addChild(m_pMafia[i], 3) ;
	}

	// ������
	CCSprite *pItemSpace[3][3] ;
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			pItemSpace[i][j] = CCSprite::create("Image/Member/Item_Space.png") ;
			pItemSpace[i][j]->setPosition(ccp(440 + (j * 100), 590 - (i * 145))) ;
			this->addChild(pItemSpace[i][j], 2) ;

			m_pItemList[i][j] = CCMenuItemImage::create("Image/UI/BuyMenu/Acohol_Icon.png", "Image/UI/BuyMenu/Acohol_Icon.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;
			m_pItemList[i][j]->setPosition(pItemSpace[i][j]->getPosition()) ;
			m_pItemList[i][j]->setEnabled(false) ;
			m_pItemList[i][j]->setVisible(false) ;
			m_pItemList[i][j]->setTag(-(i*3+j+1)) ;
			this->addChild(m_pItemList[i][j], 3) ;
		}
	}

	// ��ư
	for(i=0; i<3; i++)
	{
		m_pMoveButton[i] = CCMenuItemImage::create("Image/Member/Move_Button_1.png", "Image/Member/Move_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;
		m_pPassButton[i] = CCMenuItemImage::create("Image/Member/Pass_Button_1.png", "Image/Member/Pass_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;
		m_pItemBuyButton[i] = CCMenuItemImage::create("Image/Member/Item_Buy_Button_1.png", "Image/Member/Item_Buy_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;

		m_pMoveButton[i]->setPosition(ccp(760, 590 - (i * 145))) ;
		m_pPassButton[i]->setPosition(ccp(m_pMoveButton[i]->getPosition().x + 100, m_pMoveButton[i]->getPosition().y)) ;
		m_pItemBuyButton[i]->setPosition(ccp(m_pPassButton[i]->getPosition().x + 100, m_pPassButton[i]->getPosition().y)) ;

		m_pMoveButton[i]->setTag(0 + (i*3)) ;
		m_pPassButton[i]->setTag(1 + (i*3)) ;
		m_pItemBuyButton[i]->setTag(2 + (i*3)) ;
	}

	CCMenuItemImage *pCloseButton = CCMenuItemImage::create("Image/Member/Close_Button_1.png", "Image/Member/Close_Button_2.png", this, menu_selector(CMemberControlPopup::Menu_Click)) ;
	pCloseButton->setPosition(ccp(934, 182.5)) ;
	pCloseButton->setTag(9) ;

	CCMenu *pMenu = CCMenu::create(m_pMoveButton[0], m_pPassButton[0], m_pItemBuyButton[0],
								   m_pMoveButton[1], m_pPassButton[1], m_pItemBuyButton[1],
								   m_pMoveButton[2], m_pPassButton[2], m_pItemBuyButton[2],
								   pCloseButton, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pMenu, 2) ;

	return true ;
}

void CMemberControlPopup::SetMemberData(CMemberIcon *pMemberIcon)
{
	m_pMemberIcon = pMemberIcon ;
	SetMemberEnabled() ;
	UpdateItemList() ;
}

void CMemberControlPopup::SetAllButtonEnabled(int nIndex, bool bEnabled)
{
	SetButtonEnabled(nIndex, bEnabled, "Move") ;
	SetButtonEnabled(nIndex, bEnabled, "Pass") ;
	SetButtonEnabled(nIndex, bEnabled, "ItemBuy") ;
}

void CMemberControlPopup::UpdateItemList()
{
	int i, j ;
	int n = m_pMemberIcon->m_Member.size() ;
	CMember *pMember ;

	for(i=0; i<n; i++)
	{
		pMember = &m_pMemberIcon->m_Member[i] ;

		for(j=0; j<3; j++)
		{
			if(pMember->m_ItemList[j]!=NOTHING)
			{
				m_pItemList[i][j]->setVisible(true) ;

				switch(pMember->m_ItemList[j])
				{
				case ACOHOL :
					//m_pItemList[i][j]->setTexture(CCTextureCache::sharedTextureCache()->addImage("Image/UI/BuyMenu/Acohol_Icon.png")) ;
					m_pItemList[i][j]->setNormalImage(CCSprite::create("Image/UI/BuyMenu/Acohol_Icon.png")) ;
					break ;

				case ORIGINAL_DRINK :
					m_pItemList[i][j]->setNormalImage(CCSprite::create("Image/UI/BuyMenu/Original_Drink_Icon.png")) ;
					break ;

				case NARCOTIC :
					m_pItemList[i][j]->setNormalImage(CCSprite::create("Image/UI/BuyMenu/Narcotic_Icon.png")) ;
					break ;
				}
			}
			else
			{
				m_pItemList[i][j]->setVisible(false) ;
			}
		}
	}

	for(i=n; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			m_pItemList[i][j]->setVisible(false) ;
		}
	}
}

void CMemberControlPopup::SetButtonEnabled(int Index, bool bEnabled, const char* cButtonName)
{
	bool ButtonEnabled ;

	if(strcmp(cButtonName, "Move")==0)
	{
		ButtonEnabled = m_pMoveButton[Index]->isEnabled() ;

		if(bEnabled!=ButtonEnabled)
		{
			if(bEnabled)
				m_pMoveButton[Index]->setNormalImage(CCSprite::create("Image/Member/Move_Button_1.png")) ;
			else
				m_pMoveButton[Index]->setNormalImage(CCSprite::create("Image/Member/Move_Button_2.png")) ;

			m_pMoveButton[Index]->setEnabled(bEnabled) ;
		}
	}
	else if(strcmp(cButtonName, "Pass")==0)
	{
		ButtonEnabled = m_pPassButton[Index]->isEnabled() ;

		if(bEnabled!=ButtonEnabled)
		{
			if(bEnabled)
				m_pPassButton[Index]->setNormalImage(CCSprite::create("Image/Member/Pass_Button_1.png")) ;
			else
				m_pPassButton[Index]->setNormalImage(CCSprite::create("Image/Member/Pass_Button_2.png")) ;

			m_pPassButton[Index]->setEnabled(bEnabled) ;
		}
	}
	else if(strcmp(cButtonName, "ItemBuy")==0)
	{
		ButtonEnabled = m_pItemBuyButton[Index]->isEnabled() ;

		if(bEnabled!=ButtonEnabled)
		{
			if(bEnabled)
				m_pItemBuyButton[Index]->setNormalImage(CCSprite::create("Image/Member/Item_Buy_Button_1.png")) ;
			else
				m_pItemBuyButton[Index]->setNormalImage(CCSprite::create("Image/Member/Item_Buy_Button_2.png")) ;

			m_pItemBuyButton[Index]->setEnabled(bEnabled) ;
		}
	}
}

void CMemberControlPopup::SetMemberEnabled()
{
	int i ;
	const int num = m_pMemberIcon->m_Member.size() ;

	/*for(i=num; i<3; i++)
		MemberEnabled(i, false) ;

	for(i=0; i<num; i++)
		MemberEnabled(i, true) ;

	////
	// ���� ������ �ȵǾ��ų� ����Ǿ��� �� �̵��� �� �ִ� ������ ���ٸ�
	// ��ư�� ��Ȱ��ȭ ��Ų��
	CArea *Area = (CArea*)m_pMemberIcon->getParent() ;
	if(!g_pAreaManager->MoveRouteCheck(Area))
	{
		for(i=0; i<num; i++)
		{
			if(m_pMoveButton[i]->isEnabled())
				SetButtonEnabled(i, false, "Move") ;
		}
	}

	if(!Area->isSmuggling())
	{
		for(i=0; i<num; i++)
			SetButtonEnabled(i, false, "ItemBuy") ;
	}

	for(i=0; i<num; i++)
	{
		if(m_pMemberIcon->m_Member[i].isMove())
			SetButtonEnabled(i, false, "Move") ;
	}
	////*/
	for(i=num; i<3; i++)
	{
		m_pMafia[i]->setVisible(false) ;
		
		SetAllButtonEnabled(i, false) ;
	}

	CArea *Area = (CArea*)m_pMemberIcon->getParent() ;
	bool MoveRoute = g_pAreaManager->MoveRouteCheck(Area) ;
	for(i=0; i<num; i++)
	{
		m_pMafia[i]->setVisible(true) ;

		if(!m_pMemberIcon->m_Member[i].isBuy())
		{
			if((!MoveRoute && m_pMoveButton[i]->isEnabled()) ||	// �̵��� �� �ִ� ��Ʈ�� ���ų�
				m_pMemberIcon->m_Member[i].isMove())				// �̹� �̵��� �ѻ��¶��
				SetButtonEnabled(i, false, "Move") ;
			else
				SetButtonEnabled(i, true, "Move") ;

			if(num<2)	// �������� 2�� �̸��϶�
				SetButtonEnabled(i, false, "Pass") ;
			else
				SetButtonEnabled(i, true, "Pass") ;

			if(!Area->isSmuggling())		// ���� ������ ������ �ƴ� ��
				SetButtonEnabled(i, false, "ItemBuy") ;
			else
				SetButtonEnabled(i, true, "ItemBuy") ;
		}
		else
		{
			SetAllButtonEnabled(i, false) ;
		}
	}
}

void CMemberControlPopup::MemberEnabled(int nIndex, bool bEnabled)
{
	m_pMafia[nIndex]->setVisible(bEnabled) ;

	SetButtonEnabled(nIndex, bEnabled, "Move") ;
	SetButtonEnabled(nIndex, bEnabled, "Pass") ;
	SetButtonEnabled(nIndex, bEnabled, "ItemBuy") ;
}

void CMemberControlPopup::PassItemSender(int Index)
{
	int i ;
	int n = m_pMemberIcon->m_Member.size() ;

	m_nSenderIndex = Index ;

	for(i=0; i<n; i++)
	{
		if(i!=m_nSenderIndex)
		{
			m_pPassButton[i]->setNormalImage(CCSprite::create("Image/Member/Receipt_Button_1.png")) ;
			m_pPassButton[i]->setSelectedImage(CCSprite::create("image/Member/Receipt_Button_2.png")) ;
		}
		else
		{
			SetButtonEnabled(i, false, "Pass") ;
		}
	}
	m_bPassItem = true ;
}

void CMemberControlPopup::PassItemReceiver(int Index)
{
	int i ;

	m_nReceiverIndex = Index ;

	m_pPassButton[m_nReceiverIndex]->setNormalImage(CCSprite::create("Image/Member/Finish_Button_1.png")) ;
	m_pPassButton[m_nReceiverIndex]->setSelectedImage(CCSprite::create("Image/Member/Finish_Button_2.png")) ;

	for(i=0; i<3; i++)
		m_pItemList[m_nSenderIndex][i]->setEnabled(true) ;
}

void CMemberControlPopup::PassItem(int Index)
{
	char str[1024] ;
	sprintf(str, "%d", Index) ;
	CCMessageBox(str, "d") ;
}

void CMemberControlPopup::Menu_Click(CCObject *pSender)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	CCMenuItem *pItem = (CCMenuItem *)pSender ;
	const int tag = pItem->getTag() ;
	const int index = tag/3 ;
	CArea *pArea ;

	switch(tag)
	{
	case 0 :
	case 3 :
	case 6 :
		m_pMemberIcon->setMove(true) ;

		pArea = (CArea*)m_pMemberIcon->getParent() ;
		g_pAreaManager->MoveMemberPrepare(pArea) ;
		g_pMemberManager->MemorizeMovingData(pArea->getTag(), m_pMemberIcon, index) ;
		pDirector->popScene() ;
		break ;

	case 1 :
	case 4 :
	case 7 :
		if(!m_bPassItem)
			PassItemSender(index) ;
		else
			PassItemReceiver(index) ;
		break ;

	case 2 :
	case 5 :
	case 8 :
		g_pItemBuyPopup->SetMemberData(&m_pMemberIcon->m_Member[index], index) ;

		pDirector->popScene() ;
		pDirector->pushScene(g_pItemBuyPopup) ;
		break ;

	case -1 :
	case -2 :
	case -3 :
	case -4 :
	case -5 :
	case -6 :
	case -7 :
	case -8 :
	case -9 :
		PassItem(-((tag+1)%3)) ;
		break ;

	case 9 :
		pDirector->popScene() ;
		break ;
	}
}
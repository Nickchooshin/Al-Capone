#include "GameLayer.h"

#include "Area.h"
#include "UI.h"
#include "PopupMenu.h"
#include "Data.h"
#include "MemberManager.h"
#include "MemberControlPopup.h"

#include "AreaManager.h"

USING_NS_CC;

bool GameLayer::init()
{
	if ( !CCLayer::init() )
    {
		return false;
	}

	srand(time(NULL)) ;

	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true) ;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	g_pPopupMenu->m_pNode = this ;
	
	/*WCHAR strACP[1024] ;//
	MultiByteToWideChar( CP_ACP, 0, m_Information.c_str(), -1, strACP, 1024 ) ;//
	char strUTF8[1024];//
	WideCharToMultiByte( CP_UTF8, 0, strACP, -1, strUTF8, 1024, NULL, NULL ) ;//	°íÃÄ¾ßµÊ
	
	m_pLabelInformation = CCLabelTTF::create(strUTF8, "fonts/arial.ttf", 12, m_pImgInformation->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter) ;
	m_pLabelInformation->setPosition( m_pImgInformation->getPosition() ) ;
	m_pLabelInformation->setColor(ccc3(0, 0, 0)) ;
	m_pLabelInformation->setVisible(m_bInformation) ;
	this->addChild(m_pLabelInformation, 1) ;*/

	//m_AreaManager = CAreaManager::create() ;
	//this->addChild(m_AreaManager, 1) ;
	g_pAreaManager->init() ;
	this->addChild(g_pAreaManager, 1) ;

	g_pMemberManager->init() ;
	this->addChild(g_pMemberManager, 2) ;

	g_pMemberControlPopup->init() ;

	CUI *UI = CUI::create() ;
	this->addChild(UI, 3) ;

	scheduleUpdate() ;
    
	return true;
}

void GameLayer::update(float dt)
{
	if(g_pData->m_User.m_Turn.BeginTurnFlow())
	{
		if(g_pData->m_User.m_Turn.GetTurn()==1)
		{
			g_pAreaManager->RoundFlow() ;
		}
		g_pAreaManager->TurnFlow() ;

		g_pData->m_User.m_Turn.EndTurnFlow() ;
	}
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true ;
}

void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	g_pPopupMenu->Release() ;
}

void GameLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}
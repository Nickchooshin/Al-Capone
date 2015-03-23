#include "GameLayer.h"

#include "Area.h"
#include "UI.h"
#include "PopupMenu.h"
#include "Data.h"
#include "MemberManager.h"
#include "MemberControlPopup.h"
#include "ItemBuyPopup.h"

#include "AreaManager.h"

#include "Manager.h"

#include "EndingScene.h"
#include "GameoverScene.h"

//
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool GameLayer::init()
{
	if ( !CCLayer::init() )
    {
		return false;
	}

	srand(time(NULL)) ;

	removeAllChildrenWithCleanup(true) ;

	//
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Buy_1.mp3") ;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Buy_2.mp3") ;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Buy_3.mp3") ;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Man_allo.mp3") ;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Man_del.mp3") ;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Item_sell.wav") ;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Turn.mp3") ;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Round.mp3") ;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Block.mp3") ;
	//

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
	g_pData->init() ;

	/*g_pAreaManager->init() ;
	g_pAreaManager->removeFromParentAndCleanup(true) ;
	this->addChild(g_pAreaManager, 1) ;

	g_pMemberManager->init() ;
	g_pMemberManager->removeFromParentAndCleanup(true) ;
	this->addChild(g_pMemberManager, 2) ;*/

	CAreaManager *pAreaManager ;
	pAreaManager = CAreaManager::create() ;
	this->addChild(pAreaManager, 1) ;

	CMemberManager *pMemberManager ;
	pMemberManager = CMemberManager::create() ;
	this->addChild(pMemberManager, 2) ;

	CManager::Area = pAreaManager ;
	CManager::Member = pMemberManager ;

	g_pMemberControlPopup->init() ;

	g_pItemBuyPopup->init() ;

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
			CManager::Area->RoundFlow() ;
		}
		CManager::Area->TurnFlow() ;

		g_pData->m_User.m_Turn.EndTurnFlow() ;

		if(g_pData->m_User.m_nMoney>=g_pData->m_nEndMoney)
		{
			// Ending
			CCDirector::sharedDirector()->replaceScene(EndingScene::scene()) ;
		}
		else if(g_pData->m_User.m_nMoney<0)
		{
			// Game_over
			CCDirector::sharedDirector()->replaceScene(GameoverScene::scene()) ;
		}
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
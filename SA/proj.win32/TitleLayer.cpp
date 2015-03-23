#include "TitleLayer.h"

#include "GameScene.h"
#include "TutorialScene.h"
#include "CreditsScene.h"

USING_NS_CC;

bool TitleLayer::init()
{
	if ( !CCLayer::init() )
    {
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize() ;

	CCSprite *pMainScreen = CCSprite::create("Image/Title/Main.png") ;
	pMainScreen->setPosition(ccp(visibleSize.width/2, visibleSize.height/2)) ;
	this->addChild(pMainScreen, 0) ;

	CCMenuItemImage *pStart = CCMenuItemImage::create("Image/Title/Start_Button_1.png", "Image/Title/Start_Button_2.png", this, menu_selector(TitleLayer::Menu_Click)) ;
	pStart->setPosition(ccp(640, 320)) ;
	pStart->setTag(0) ;

	CCMenuItemImage *pTutorial = CCMenuItemImage::create("Image/Title/Tutorial_Button_1.png", "Image/Title/Tutorial_Button_2.png", this, menu_selector(TitleLayer::Menu_Click)) ;
	pTutorial->setPosition(ccp(640, 270)) ;
	pTutorial->setTag(1) ;

	CCMenuItemImage *pCredits = CCMenuItemImage::create("Image/Title/Credits_Button_1.png", "Image/Title/Credits_Button_2.png", this, menu_selector(TitleLayer::Menu_Click)) ;
	pCredits->setPosition(ccp(640, 220)) ;
	pCredits->setTag(2) ;

	CCMenuItemImage *pExit = CCMenuItemImage::create("Image/Title/Exit_Button_1.png", "Image/Title/Exit_Button_2.png", this, menu_selector(TitleLayer::Menu_Click)) ;
	pExit->setPosition(ccp(640, 170)) ;
	pExit->setTag(3) ;

	CCMenu *pMenu = CCMenu::create(pStart, pTutorial, pCredits, pExit, NULL) ;
	pMenu->setPosition(ccp(0, 0)) ;
	this->addChild(pMenu, 1) ;
    
	return true;
}

void TitleLayer::update(float dt)
{
}

bool TitleLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true ;
}

void TitleLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void TitleLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void TitleLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void TitleLayer::Menu_Click(CCObject *pSender)
{
	CCMenuItem *pItem = (CCMenuItem *)pSender ;
	const int tag = pItem->getTag() ;

	CCDirector *pDirector = CCDirector::sharedDirector() ;

	switch(tag)
	{
	case 0 :
		pDirector->replaceScene(GameScene::scene()) ;
		break ;

	case 1 :
		pDirector->replaceScene(TutorialScene::scene()) ;
		break ;

	case 2 :
		pDirector->replaceScene(CreditsScene::scene()) ;
		break ;

	case 3 :
		pDirector->end() ;
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
		#endif
		break ;
	}
}
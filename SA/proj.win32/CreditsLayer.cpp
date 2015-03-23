#include "CreditsLayer.h"

#include "TitleScene.h"

USING_NS_CC;

bool CreditsLayer::init()
{
	if ( !CCLayer::init() )
    {
		return false;
	}

	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true) ;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize() ;

	CCSprite *pCreditsImage = CCSprite::create("Image/Credits/Credits_Image.png") ;
	pCreditsImage->setPosition(ccp(visibleSize.width/2, visibleSize.height/2)) ;
	this->addChild(pCreditsImage, 0) ;

	SetLabel() ;

	m_fTime = 0.0f ;

	scheduleUpdate() ;
    
	return true;
}

void CreditsLayer::update(float dt)
{
	m_fTime += dt ;

	if(m_fTime>=900.0f)
		m_pLabel->setVisible(true) ;
}

bool CreditsLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCDirector *pDirector = CCDirector::sharedDirector() ;
	pDirector->replaceScene(TitleScene::scene()) ;

	return true ;
}

void CreditsLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CreditsLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CreditsLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CreditsLayer::SetLabel()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize() ;

	char str[1024] ;
	WCHAR wstr[1024] ;

	sprintf(str, " shekqxla. \n tkfka Rmfduemfdls rlghlrwksms dkanrjteh dksgkrh cushfrh, \n rmfovlrdms gkswnaksdp Rmxsosekejs apdlsghkaus rmfovlrdmf 2wnrk sjaehfhr dhkstjdeh dksgkrh akwlakrskfdp wwclrh, \n gkdurks rmEkstlrdmfh gkfRjaus gkqtnrdlrh skqkfdlrh ek Eofucufk TlqkftoRlemfdk") ;
	MultiByteToWideChar( CP_ACP, 0, str, -1, wstr, 1024 ) ;
	WideCharToMultiByte( CP_UTF8, 0, wstr, -1, str, 1024, NULL, NULL ) ;

	m_pLabel = CCLabelTTF::create(str, "fonts/arial.ttf", 18) ;
	m_pLabel->setPosition(ccp(visibleSize.width/2, visibleSize.height/2)) ;
	m_pLabel->setVisible(false) ;
	this->addChild(m_pLabel, 5) ;
}
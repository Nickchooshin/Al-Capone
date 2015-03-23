#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

#include <crtdbg.h>//

#define CRTDBG_MAP_ALLOC//
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)//

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) ;//

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("Al Capone - 1.00v sound");
    //eglView->setFrameSize(480, 320);
	eglView->setFrameSize(1280, 720) ;
    return CCApplication::sharedApplication()->run();
}
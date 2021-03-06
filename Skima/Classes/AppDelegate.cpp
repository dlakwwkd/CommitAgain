#include "pch.h"
#include "AppDelegate.h"
#include "MainScene.h"
#include "TcpClient.h"
#include "Macros.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::~AppDelegate()
{
    CocosDenshion::SimpleAudioEngine::end();
    TcpClient::getInstance()->destroyInstance();
}

void AppDelegate::initGLContextAttrs()
{
    //red,green,blue,alpha,depth,stencilx
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) 
	{
        glview = GLViewImpl::create("Amaging PVP Game: Skima");
        director->setOpenGLView(glview);

		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);

        glview->setFrameSize(DISPLAY_X, DISPLAY_Y);
        glview->setDesignResolutionSize(MAX_MAP_SIZE_X, MAX_MAP_SIZE_Y, ResolutionPolicy::NO_BORDER);
    }

    // turn on display FPS
    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MainScene::createScene();

    // run
	director->runWithScene(scene);
    return true;
}



void AppDelegate::applicationDidEnterBackground()
{
    //Director::getInstance()->stopAnimation();
}
void AppDelegate::applicationWillEnterForeground()
{
    //Director::getInstance()->startAnimation();
}

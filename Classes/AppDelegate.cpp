#include "AppDelegate.h"
#include "GameScene.h"
#include "../Utilities/ns.h"
#include "SimpleAudioEngine.h"

#define FPS 60

USING_NS_CATS;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
    cocos2d::CCEGLView* pEGLView = cocos2d::CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / FPS);
    
    cocos2d::CCSize screenSize = cocos2d::CCEGLView::sharedOpenGLView()->getFrameSize();
    //CCSize designSize = CCSizeMake(480, 320);
    cocos2d::CCSize designSize = cocos2d::CCSizeMake(360, 720);
    std::vector<std::string> searchPaths;

    // create a scene. it's an autorelease object
    cocos2d::CCScene *pScene = GameScene::scene();
    
    cocos2d::CCLog("Screen width = %f height = %f\n", screenSize.width, screenSize.height);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//IOS Specific Settings
	// OpenGLView initialized in testsAppDelegate.mm on ios platform
	//if device's screen width is greater than 768, use high definition images

	if (screenSize.width >= 640) {
		CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone5");
		pDirector->setContentScaleFactor(1136.0f / designSize.height);

		//or else, use standard definition
	} else {
		CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");

		pDirector->setContentScaleFactor(1024.0f / designSize.height);

	}

#else
	//Other OS settings. TESTED OK in Android and BlackBerry 10

	if (screenSize.height >= 1280) {
		//High Resolution
		searchPaths.push_back("hd");
		pDirector->setContentScaleFactor(1280.0f / designSize.height);

	} else if (screenSize.height >= 800) {
		//Mid resolution
		searchPaths.push_back("md");
		pDirector->setContentScaleFactor(800.0f / designSize.height);

	} else {
		//Low resolution
		searchPaths.push_back("sd");
		pDirector->setContentScaleFactor(320.0f / designSize.height);

	}
#endif
	cocos2d::CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
	cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionExactFit);

    // run
    pDirector->runWithScene(pScene);

    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    cocos2d::CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    cocos2d::CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

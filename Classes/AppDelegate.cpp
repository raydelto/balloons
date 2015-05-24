#include "AppDelegate.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

#define FPS 60

USING_NS_CC;


AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{
}


bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
    	CCLOG("!glview");
        glview = GLViewImpl::create("Save the balloons");
		glview->setFrameSize(480, 800);
        director->setOpenGLView(glview);
    }
	std::vector<std::string> searchPaths;
	Size screenSize = glview->getFrameSize();
	CCLOG("Screen size = w = %f , %f", screenSize.width, screenSize.height);
//	Size designSize(768, 1280);
	Size designSize(360, 720);

	searchPaths.push_back("sounds");
	//searchPaths.push_back("particles");
	director->setContentScaleFactor(1);

	if (screenSize.height > 800)
	{
		//High Resolution
		searchPaths.push_back("images/high");
		//director->setContentScaleFactor(1280.0f / designSize.height);
//		director->setContentScaleFactor(1);
	}
	else
	{
		//Mid resolution
		searchPaths.push_back("images/mid");
//		director->setContentScaleFactor(800.0f / designSize.height);
	}
	FileUtils::getInstance()->setSearchPaths(searchPaths);
	CCLOG("Search paths");
	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
    auto scene = GameScene::createScene();
    director->runWithScene(scene);
    return true;
}



// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

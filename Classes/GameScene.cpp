#include "GameScene.h"
#include "Backgrounds/Simple.h"
#include "Sprites/Balloon.h"
#include "SimpleAudioEngine.h"
#include "Common/SCScene.h"

//GameScene::GameScene() {
//    SCScene();
//}
cocos2d::CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    cocos2d::CCScene *scene = cocos2d::CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    SCScene::init();
    //////////////////////////////
    // 1. super init first
    if ( !cocos2d::CCLayer::init() )
    {
        return false;
    }
    
    cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
    cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    cocos2d::CCMenuItemImage *pCloseItem = cocos2d::CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    cocos2d::CCMenu* pMenu = cocos2d::CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(cocos2d::CCPointZero);
    this->addChild(pMenu, 1);
    
    Simple* pBackground = Simple::createWithFile("Backgrounds/Simple.png");
	pBackground->setScale(1);
    pBackground->setAnchorPoint(ccp(0,0));
    pBackground->setPosition(ccp(0,0));
    this->addChild(pBackground, 0);
    
    Balloon* pBalloon = Balloon::createWithFile("Sprites/Balloon.png");
    pBalloon->setAnchorPoint(ccp(0,0));
    pBalloon->setXY(170, 10);
    pBalloon->setSpeedY(20);
    pBalloon->setSpeedX(0);
    this->addObject(pBalloon);
    this->m_balloon = pBalloon;
    this->addChild(pBalloon, 3);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    cocos2d::CCLabelTTF* pLabel = cocos2d::CCLabelTTF::create("Save The Balloons", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 5);

    
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.ogg", true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(
                    this, 0);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/Background.wav");
    
    return true;
}

void GameScene::updateGame(float dt) {
    if (this->m_gameOver) {
        this->unschedule(schedule_selector(GameScene::updateGame));
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("uh.wav", false);
        //GameOverScene *pScene = GameOverScene::create();
        //char scoreText[128];
        //sprintf(scoreText, "%d", m_playerScore);
        //pScene->getLayer()->getLabel()->setString(scoreText);
        //CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,pScene));
        //CCDirector::sharedDirector()->replaceScene(pScene);
        return;
    }
}


void GameScene::menuCloseCallback(cocos2d::CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	cocos2d::CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    cocos2d::CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

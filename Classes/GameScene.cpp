#include "GameScene.h"
#include "Backgrounds/Simple.h"
#include "Sprites/Balloon.h"
#include "SimpleAudioEngine.h"
#include "Common/SCScene.h"

GameScene::GameScene(): m_background(NULL), m_balloon(NULL), m_gameOver(false), m_btnInflar(NULL), m_btnDesinflar(NULL) {
    m_winSize = CCDirector::sharedDirector()->getWinSize();
}
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


void GameScene::initButtons()
{
	CCLog("Width = %f , Height = %f", m_winSize.width , m_winSize.height);
	m_btnInflar = CCSprite::create("Sprites/btn_inflar.png");
	m_btnDesinflar = CCSprite::create("Sprites/btn_desinflar.png");	
	m_btnInflar -> setPosition(ccp(m_winSize.width-m_btnDesinflar->getContentSize().width, m_winSize.height*0.05));
	m_btnDesinflar -> setPosition(ccp(0, m_winSize.height*0.05));
	m_btnInflar->setAnchorPoint(CCPointZero);
	m_btnDesinflar->setAnchorPoint(CCPointZero);
	this->addChild(m_btnInflar, 4);
	this->addChild(m_btnDesinflar, 4);


}


bool GameScene::init()
{
    SCScene::init();
    if ( !cocos2d::CCLayer::init() )
    {
        return false;
    }
	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	initButtons();
    
    cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
    cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();

    cocos2d::CCMenuItemImage *pCloseItem = cocos2d::CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		m_winSize.height - pCloseItem->getContentSize().height/2));

    cocos2d::CCMenu* pMenu = cocos2d::CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(cocos2d::CCPointZero);
    this->addChild(pMenu, 1);
    
    m_background = Simple::createWithFile("Backgrounds/scrolling_bg1_sd.png");
	m_background->setScale(1);
    m_background->setAnchorPoint(ccp(0,0));
    m_background->setPosition(ccp(0,0));
    this->addChild(m_background, 0);
    
    this->m_balloon = Balloon::createWithFile("Sprites/balloon_sc.png");
    this->m_balloon->setAnchorPoint(ccp(0,0));
    this->m_balloon->setXY(170, 10);
    this->m_balloon->setSpeedY(DEFAULT_Y_SPEED);
    this->m_balloon->setSpeedX(0);
	this->m_balloon->setPosition(ccp(m_winSize.width/2, m_winSize.height*0.05));
    this->addObject(this->m_balloon);    
    this->addChild(this->m_balloon, 3);

  
       
    /*CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(
                    this, 0);*/
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/Background.mp3", true);

	this->schedule(schedule_selector(GameScene::updateGame));
    
    return true;
}

void GameScene::updateGame(float dt) {		
    if (this->m_gameOver) {
        this->unschedule(schedule_selector(GameScene::updateGame));
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("uh.wav", false);
		/*m_background->setPosition(ccp(0,0));
		this->m_balloon->setPosition(ccp(m_winSize.width/2, m_winSize.height*0.05));*/

		//m_gameOver = false;


		cocos2d::CCLabelTTF* pLabel = cocos2d::CCLabelTTF::create("Congratulations!, you won!", "Arial", 24);
		CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
        this->addChild(pLabel, 5);
        return;
    }
	
	scrollScene(dt);
	if (m_background -> getPositionY() < (( m_background->getContentSize().height * -1 ) + m_winSize.height)){        
		m_gameOver = true;
	 }
    
}
	
void GameScene::scroll(CCSprite* sprite, float dt, int direction)
{
	sprite -> setPositionY(sprite->getPositionY()  +  (( m_balloon->getSpeedY() *dt) * direction) );
}

void GameScene::scrollBaloon(float dt)
{
//	m_balloon -> setPositionY(m_balloon->getPositionY() -( m_balloon->getSpeedY() *dt));	
	scroll(m_balloon, dt,1);
}


void GameScene::scrollScene(float dt)
{
	if(m_balloon->getPositionY() > (m_winSize.height * 0.1))
	{
		    //this->m_Y += this->m_speedY * dt;
		//m_background -> setPositionY(m_background->getPositionY() -( m_balloon->getSpeedY() *dt));
		scroll(m_background,dt,-1);

	}else{
		scrollBaloon(dt);
	}
	
}

void GameScene::ccTouchesEnded(CCSet* touches, CCEvent* event) 
{
	this->unschedule(schedule_selector(GameScene::inflarGlobo));
	this->unschedule(schedule_selector(GameScene::desinflarGlobo));
	m_balloon->setSpeedY(DEFAULT_Y_SPEED);
}

void GameScene::inflarGlobo(float dt)
{	
	scroll(m_balloon, dt,1);
	m_balloon->setSpeedY(m_balloon->getSpeedY() + dt);
}

void GameScene::desinflarGlobo(float dt)
{
	scroll(m_balloon, dt,-1);
	m_balloon->setSpeedY(m_balloon->getSpeedY() - dt);

}



void GameScene::ccTouchesBegan(CCSet* touches, CCEvent* event) 
{
	CCTouch* touch = (CCTouch*) (touches->anyObject());
	CCPoint location = touch->getLocation();

	if (collisions(m_btnInflar, &location)) {
		//scroll(m_balloon,1,1);
		this->schedule(schedule_selector(GameScene::inflarGlobo));
		CCLog("INFLA!");
	} else if (collisions(m_btnDesinflar, &location)) {
		CCLog("DESINFLA!");
		//scroll(m_balloon,1,-1);
		this->schedule(schedule_selector(GameScene::desinflarGlobo));
	}
}


bool GameScene::collisions(cocos2d::CCSprite* sprite,
		cocos2d::CCPoint* point) {
	CCPoint position = sprite->getPosition();
	CCSize size = sprite->getContentSize();
	CCRect spriteRect = CCRectMake(position.x, position.y, size.width,
			size.height);
	return spriteRect.containsPoint(*point);
}

bool GameScene::collisions(cocos2d::CCSprite* sprite1,
		cocos2d::CCSprite* sprite2) {
	CCPoint position1 = sprite1->getPosition();
	CCSize size1 = sprite1->getContentSize();
	CCRect spriteRect1 = CCRectMake(position1.x, position1.y, size1.width,
			size1.height);

	CCPoint position2 = sprite2->getPosition();
	CCSize size2 = sprite2->getContentSize();
	CCRect spriteRect2 = CCRectMake(position2.x, position2.y, size2.width,
			size2.height);
	return spriteRect1.intersectsRect(spriteRect2);
}

void GameScene::keyBackClicked(void) {
		CCLog("\nKeyBack pressed\n");
		CCDirector::sharedDirector()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
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

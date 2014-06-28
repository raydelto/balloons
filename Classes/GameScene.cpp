#include "GameScene.h"
#include "Backgrounds/Simple.h"
#include "Sprites/Balloon.h"
#include "SimpleAudioEngine.h"
#include "Common/SCScene.h"

GameScene::GameScene(): m_gameOver(false), m_won(false) {
    m_winSize = CCDirector::sharedDirector()->getWinSize();
	abanicos = new CCArray();
	ramas = new CCArray();
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

void GameScene::initRamas()
{

	CCSprite* rama = NULL;
	//TODO: 1874 es el valor hardcoded de la altura del diseño, escribir de manera autoajustable
	float positionRatio = 1874  / NUM_RAMAS;
	float positionY = positionRatio;
	float positionX = 0;

	
	for(int i = 1 ; i <= NUM_RAMAS ; i++)
	{
		
		rama = i % 3 == 0 ? CCSprite::create("Sprites/rama_triple.png") : CCSprite::create("Sprites/rama_doble.png");
		if(i % 2 == 0)
		{
			positionX = 0;
			
			rama -> setFlipX(true);
		}else
		{
			positionX = m_winSize.width - rama->getContentSize().width;
				
		}
		rama->setAnchorPoint(CCPointZero);
		rama->setPosition(ccp(positionX, positionY));
		CCObject* iterator = NULL;
		CCARRAY_FOREACH(abanicos, iterator)
		{
			CCSprite* abanico = dynamic_cast<CCSprite*>(iterator);
			if(collisions(abanico,rama))
			{
				CC_SAFE_RELEASE_NULL(rama);
				break;
				
			}
		}
		positionY += positionRatio;

		if(rama == NULL)
		{
			continue;
		}

		this->addChild(rama,3);
		ramas->addObject(rama);		

	}


}

void GameScene::initAbanicos()
{
	CCSprite* abanico = NULL;
	//TODO: 1874 es el valor hardcoded de la altura del diseño, escribir de manera autoajustable
	float positionRatio = 1874  / NUM_ABANICOS;
	float positionY = positionRatio;
	float positionX = 0;

	for(int i = 1 ; i <= NUM_ABANICOS ; i++)
	{
		abanico = CCSprite::create("Sprites/abanico.png");
		abanico->setAnchorPoint(CCPointZero);

		if(i % 2 == 0)
		{
			positionX = 0;
			abanico -> setFlipX(true);
		}else
		{
			positionX = m_winSize.width - abanico->getContentSize().width;
				
		}
		abanico->setPosition(ccp(positionX, positionY));
		this->addChild(abanico,3);
		abanicos->addObject(abanico);
		positionY += positionRatio;

	}


}


void GameScene::initCloseMenu()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		m_winSize.height - pCloseItem->getContentSize().height/2));

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(cocos2d::CCPointZero);
    this->addChild(pMenu, 4);
}


void GameScene::initBackground()
{
    m_background = Simple::createWithFile("Backgrounds/scrolling_bg1_sd.png");
	m_background->setScale(1);
    m_background->setAnchorPoint(ccp(0,0));
    m_background->setPosition(ccp(0,0));
    this->addChild(m_background, 0);
}

void GameScene::initBalloon()
{
    this->m_balloon = Balloon::createWithFile("Sprites/balloon_sc.png");
    this->m_balloon->setAnchorPoint(ccp(0,0));
    this->m_balloon->setXY(170, 10);
    this->m_balloon->setSpeedY(DEFAULT_Y_SPEED);
    this->m_balloon->setSpeedX(0);
	this->m_balloon->setPosition(ccp(m_winSize.width/2, m_winSize.height*0.05));
    this->addObject(this->m_balloon);    
    this->addChild(this->m_balloon, 3);

}



bool GameScene::init()
{    
    if ( !CCLayer::init() )
    {
		CCLog("Error al iniciar escena");
        return false;
    }
	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	initButtons();
	initCloseMenu();
	initBackground();
	initBalloon();
	initAbanicos();  
	initRamas();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/Background.mp3", true);
	this->schedule(schedule_selector(GameScene::updateGame));    
    return true;
}

void GameScene::updateViento(float dt) 
{
	if(m_balloon->getTag() == BALLOON_IS_MOVING)
	{
		return;
	}
		CCObject* iterator = NULL;
		CCRect alcanceAbanico;
		CCRect rectBalloon;
		CCARRAY_FOREACH(abanicos, iterator)
		{
			CCSprite* abanico = dynamic_cast<CCSprite*>(iterator);
			alcanceAbanico = CCRectMake(0, abanico->getPositionY(), m_winSize.width, abanico->getContentSize().height);
			CCSize balloonSize = m_balloon->getContentSize();
			rectBalloon = CCRectMake(m_balloon->getPositionX(), m_balloon->getPositionY(), balloonSize.width,	balloonSize.height);
			int direction = 1;
			float newX = 0.0f;
			if(alcanceAbanico.intersectsRect(rectBalloon))
			{
				if(abanico->getTag() == FAN_BLOWED)
				{
					continue;
				}
				CCLog("Contacto con abanico!");
				direction = abanico->isFlipX() ? 1 : -1;
				newX = m_balloon->getPositionX() + (m_winSize.width * 0.25 * direction);
				CCLog("newX = %f" , newX);
				m_balloon ->setTag(BALLOON_IS_MOVING);
				abanico->setTag(FAN_BLOWED);
				CCFiniteTimeAction* actionMove = NULL;
				CCFiniteTimeAction* actionMoveDone = NULL;
				actionMove = CCMoveTo::create(3.0f,	ccp(newX, m_balloon->getPositionY() + 10));
				actionMoveDone = CCCallFuncN::create(this,	callfuncN_selector(GameScene::balloonMoveFinished));
				m_balloon->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));

			}
		}
}

void GameScene::balloonMoveFinished(CCNode* sender) 
{
	CCLog("Balloon move finished!!");
	m_balloon->setTag(0);
}


void GameScene::updateGame(float dt) 
{		
    if(m_gameOver)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/pop.wav");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		m_balloon->setVisible(false);
		showMessage("Game Over");
		this->unschedule(schedule_selector(GameScene::updateGame));        	
		return;
	}
	if (m_won) 
	{
        this->unschedule(schedule_selector(GameScene::updateGame));        
		showMessage("Congratulations!, you won!");
        return;
    }
	
	scrollScene(dt);
	updateViento(dt);
	checkCollisions();
	if (m_background -> getPositionY() < (( m_background->getContentSize().height * -1 ) + m_winSize.height)){        
		m_won = true;
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

void GameScene::showMessage(const char* message)
{
		cocos2d::CCLabelTTF* pLabel = cocos2d::CCLabelTTF::create(message, "Arial", 24);
		CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
        this->addChild(pLabel, 5);
}

void GameScene::scrollScene(float dt)
{
	if(m_balloon->getPositionY() > (m_winSize.height * 0.1))
	{
		scroll(m_background,dt,-1);
		//Haciendo scroll de los abanicos
		CCObject* iterator = NULL;
		CCARRAY_FOREACH(abanicos, iterator)
		{
			CCSprite* abanico = dynamic_cast<CCSprite*>(iterator);
			scroll(abanico,dt,-1);

		}

		CCARRAY_FOREACH(ramas, iterator)
		{
			CCSprite* rama = dynamic_cast<CCSprite*>(iterator);
			scroll(rama,dt,-1);

		}

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
	m_balloon->setSpeedY(m_balloon->getSpeedY() + (dt*30));
}

void GameScene::desinflarGlobo(float dt)
{
	scroll(m_balloon, dt,-1);
	m_balloon->setSpeedY(m_balloon->getSpeedY() - dt);

}



void GameScene::ccTouchesBegan(CCSet* touches, CCEvent* event) 
{
	if(m_gameOver || m_won)
	{
		return;
	}

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

void GameScene::checkCollisions()
{
		CCObject* iterator = NULL;
		CCPoint position = m_balloon->getPosition();
		CCSize size = m_balloon->getContentSize();
		CCRect balloonRect = CCRectMake(position.x , position.y+(size.height/2), size.width,	size.height/2);

		CCARRAY_FOREACH(ramas, iterator)
		{
			CCSprite* rama = dynamic_cast<CCSprite*>(iterator);

			if(collisions(balloonRect,rama))
			{
				m_gameOver = true;
				break;
			}
		}
}


bool GameScene::collisions(CCRect& rectangle,CCSprite* sprite) 
{
	CCPoint position = sprite->getPosition();
	CCSize size = sprite->getContentSize();
	CCRect spriteRect = CCRectMake(position.x, position.y, size.width,	size.height);
	return spriteRect.intersectsRect(rectangle);
}

bool GameScene::collisions(CCSprite* sprite,CCPoint* point) 
{
	CCPoint position = sprite->getPosition();
	CCSize size = sprite->getContentSize();
	CCRect spriteRect = CCRectMake(position.x, position.y, size.width,	size.height);
	return spriteRect.containsPoint(*point);
}

bool GameScene::collisions(CCSprite* sprite1, CCSprite* sprite2) 
{
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

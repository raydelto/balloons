#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../cocos2d/cocos/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#endif
USING_NS_CC;
using namespace CocosDenshion;
GameScene::GameScene(): m_gameOver(false), m_won(false), initialized(false),m_balloon(nullptr), m_background(nullptr)
{
    m_winSize = Director::getInstance()->getWinSize();
}

/*cocos2d::CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    cocos2d::CCScene *scene = cocos2d::CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}*/

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


void GameScene::initButtons()
{
	CCLOG("Width = %f , Height = %f", m_winSize.width , m_winSize.height);
	m_btnInflar = Sprite::create("Sprites/btn_inflar.png");
	m_btnDesinflar = Sprite::create("Sprites/btn_desinflar.png");
	m_btnInflar -> setPosition(Vec2(m_winSize.width-m_btnDesinflar->getContentSize().width, m_winSize.height*0.05));
	m_btnDesinflar -> setPosition(Vec2(0, m_winSize.height*0.05));
	m_btnInflar->setAnchorPoint(Vec2::ZERO);
	m_btnDesinflar->setAnchorPoint(Vec2::ZERO);
	this->addChild(m_btnInflar, 4);
	this->addChild(m_btnDesinflar, 4);
}

void GameScene::initRamas()
{

	Sprite* rama = nullptr;
	//TODO: 1874 es el valor hardcoded de la altura del diseño, escribir de manera autoajustable
	float positionRatio = 1874  / NUM_RAMAS;
	float positionY = positionRatio;
	float positionX = 0;

	
	for(int i = 1 ; i <= NUM_RAMAS ; i++)
	{
		
		rama = i % 3 == 0 ? Sprite::create("Sprites/rama_triple.png") : Sprite::create("Sprites/rama_doble.png");
		if(i % 2 == 0)
		{
			positionX = 0;
			
			rama -> setFlipX(true);
		}else
		{
			positionX = m_winSize.width - rama->getContentSize().width;
				
		}
		rama->setAnchorPoint(Vec2::ZERO);
		rama->setPosition(Vec2(positionX, positionY));
		for(auto abanico : abanicos)
		{
			if(collisions(abanico,rama))
			{
				CCLOG("remueve rama");
				CC_SAFE_RELEASE_NULL(rama);
				break;
				
			}
		}
		positionY += positionRatio;

		if(rama == nullptr)
		{
			continue;
		}

		this->addChild(rama,3);
		ramas.pushBack(rama);

	}


}

void GameScene::initAbanicos()
{
	Sprite* abanico = nullptr;
	//TODO: 1874 es el valor hardcoded de la altura del diseño, escribir de manera autoajustable
	float positionRatio = 1874  / NUM_ABANICOS;
	float positionY = positionRatio;
	float positionX = 0;

	for(int i = 1 ; i <= NUM_ABANICOS ; i++)
	{
		abanico = Sprite::create("Sprites/abanico.png");
		abanico->setAnchorPoint(Vec2::ZERO);

		if(i % 2 == 0)
		{
			positionX = 0;
			abanico -> setFlipX(true);
		}else
		{
			positionX = m_winSize.width - abanico->getContentSize().width;
				
		}
		abanico->setPosition(Vec2(positionX, positionY));
		this->addChild(abanico,3);
		abanicos.pushBack(abanico);
		positionY += positionRatio;

	}


}


void GameScene::initCloseMenu()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto pCloseItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
										CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	pCloseItem->setPosition(Vec2(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		m_winSize.height - pCloseItem->getContentSize().height/2));

    auto pMenu = Menu::create(pCloseItem, nullptr);
    pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, 4);
}



void  GameScene::initRestartMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    MenuItemImage *mnuRestartImage = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
    									CC_CALLBACK_1(GameScene::menuRestartCallback, this));
    
	mnuRestartImage->setPosition(Vec2(visibleSize.width /2 , visibleSize.height/2));

    Menu* pMenu = Menu::create(mnuRestartImage, nullptr);
    pMenu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(pMenu, 4);

}


void GameScene::menuRestartCallback(CCObject* pSender)
{
	CCLOG("Reimplement restart logic");

}



void GameScene::initBackground()
{
    m_background = Sprite::create("Backgrounds/scrolling_bg1_sd.png");
	m_background->setScale(1);
    m_background->setAnchorPoint(Vec2::ZERO);
    m_background->setPosition(Vec2(Vec2::ZERO));
    this->addChild(m_background, 0);
}

void GameScene::initBalloon()
{
    this->m_balloon =  Balloon::createWithFile("Sprites/balloon_sc.png");
    this->m_balloon->setAnchorPoint(Vec2(0,0));
    this->m_balloon->setXY(170, 10);
    this->m_balloon->setSpeedY(DEFAULT_Y_SPEED);
    this->m_balloon->setSpeedX(0);
	this->m_balloon->setPosition(Vec2(m_winSize.width/2, m_winSize.height*0.05));
    //this->addObject(this->m_balloon);
    this->addChild(this->m_balloon, 3);

}



bool GameScene::init()
{    
	CCLOG("Init");
    if  (!Layer::init() )
    {
		CCLOG("Error al iniciar escena");
        return false;
    }

	
	m_won = false;
	m_gameOver = false;
	CCLOG("AA");
	initBackground();
	CCLOG("AA2");
	initBackButtonListener();
	CCLOG("AA3");
	initButtons();
	initCloseMenu();
	initRamas();
	initAbanicos();
	initTouch();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Background.mp3", true);

	initBalloon();


	CCLOG("B");

	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateGame));
	CCLOG("C");

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	setKeepScreenOnJni(true);
	#endif
	CCLOG("D");
	CCLOG("INIT Finished");
    return true;
}


void GameScene::initTouch()
{
	CCLOG("init touch");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::ccTouchesBegan,this);
	listener->onTouchMoved = [=](Touch* touch, Event* event){};
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::ccTouchesEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}



void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->end();
	}
}


void GameScene::initBackButtonListener()
{
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){};
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void GameScene::updateViento(float dt) 
{
	if(m_balloon->getTag() == BALLOON_IS_MOVING)
	{
		return;
	}
		Rect alcanceAbanico;
		Rect rectBalloon;
		for(auto abanico:abanicos)
		{
			alcanceAbanico = Rect(0, abanico->getPositionY(), m_winSize.width, abanico->getContentSize().height);
			Size balloonSize = m_balloon->getContentSize();
			rectBalloon = Rect(m_balloon->getPositionX(), m_balloon->getPositionY(), balloonSize.width,	balloonSize.height);
			int direction = 1;
			float newX = 0.0f;
			if(alcanceAbanico.intersectsRect(rectBalloon))
			{
				if(abanico->getTag() == FAN_BLOWED)
				{
					continue;
				}
				CCLOG("Contacto con abanico!");
				direction = abanico->isFlipX() ? 1 : -1;
				newX = m_balloon->getPositionX() + (m_winSize.width * 0.25 * direction);
				CCLOG("newX = %f" , newX);
				m_balloon ->setTag(BALLOON_IS_MOVING);
				abanico->setTag(FAN_BLOWED);
				FiniteTimeAction* actionMove = nullptr;
				FiniteTimeAction* actionMoveDone = nullptr;
				actionMove = MoveTo::create(3.0f,	Vec2(newX, m_balloon->getPositionY() + 10));
				actionMoveDone = CallFuncN::create(this,	callfuncN_selector(GameScene::balloonMoveFinished));
				m_balloon->runAction(Sequence::create(actionMove, actionMoveDone, nullptr));

			}
		}
}

void GameScene::balloonMoveFinished(Node* sender)
{
	CCLOG("Balloon move finished!!");
	m_balloon->setTag(0);
}


void GameScene::updateGame(float dt) 
{		
    if(m_gameOver)
	{
		SimpleAudioEngine::getInstance()->playEffect("Sounds/pop.wav");
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		m_balloon->setVisible(false);
		//showMessage("Game Over");
		_director->replaceScene(TransitionFlipX::create(1.0, GameOver::createScene()));

		this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::updateGame));
		//this->initRestartMenu();
		return;
	}
	if (m_won) 
	{
        this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::updateGame));
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
	
void GameScene::scroll(Sprite* sprite, float dt, int direction)
{
	sprite -> setPositionY(sprite->getPositionY()  +  (( m_balloon->getSpeedY() *dt) * direction) );
}

void GameScene::scrollBaloon(float dt)
{
	m_balloon -> setPositionY(m_balloon->getPositionY() -( m_balloon->getSpeedY() *dt));
	scroll(m_balloon, dt,1);
}

void GameScene::showMessage(const char* message)
{
	CCLOG("SHOW MESSAGE");
	CCLOG("Message = %s", message);
	auto pLabel = Label::createWithTTF(message, "fonts/Marker Felt.ttf", 24);
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	pLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
        this->addChild(pLabel, 5);
    CCLOG("SHOW MESSAGE EXIT");
}

void GameScene::scrollScene(float dt)
{
	if(m_balloon->getPositionY() > (m_winSize.height * 0.1))
	{
		scroll(m_background,dt,-1);
		//Haciendo scroll de los abanicos
		for(auto abanico: abanicos)
		{
			scroll(abanico,dt,-1);

		}

		for(auto rama: ramas)
		{
			scroll(rama,dt,-1);

		}

	}else{
		scrollBaloon(dt);
	}
	
}

void GameScene::ccTouchesEnded(Touch* touch, Event* event)
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



bool GameScene::ccTouchesBegan(Touch* touch, Event* event)
{
	CCLOG("TOUCH!");
	if(m_gameOver || m_won)
	{
		return true;
	}
	Point location = touch->getLocation();

	if (collisions(m_btnInflar, &location)) {
		scroll(m_balloon,1,1);
		this->schedule(schedule_selector(GameScene::inflarGlobo));
		CCLOG("INFLA!");
	} else if (collisions(m_btnDesinflar, &location)) {
		CCLOG("DESINFLA!");
		scroll(m_balloon,1,-1);
		this->schedule(schedule_selector(GameScene::desinflarGlobo));
	}
	return true;
}

void GameScene::checkCollisions()
{
		Point position = m_balloon->getPosition();
		Size size = m_balloon->getContentSize();
		Rect balloonRect = Rect(position.x , position.y+(size.height/2), size.width,	size.height/2);

		for(auto rama: ramas)
		{
			if(collisions(balloonRect,rama))
			{
				m_gameOver = true;
				break;
			}
		}
}


bool GameScene::collisions(Rect& rectangle,Sprite* sprite)
{
	Point position = sprite->getPosition();
	Size size = sprite->getContentSize();
	Rect spriteRect = Rect(position.x, position.y, size.width,	size.height);
	return spriteRect.intersectsRect(rectangle);
}

bool GameScene::collisions(Sprite* sprite,Point* point)
{
	Point position = sprite->getPosition();
	Size size = sprite->getContentSize();
	Rect spriteRect = Rect(position.x, position.y, size.width,	size.height);
	return spriteRect.containsPoint(*point);
}

bool GameScene::collisions(Sprite* sprite1, Sprite* sprite2)
{
	Point position1 = sprite1->getPosition();
	Size size1 = sprite1->getContentSize();
	Rect spriteRect1 = Rect(position1.x, position1.y, size1.width,
			size1.height);

	Point position2 = sprite2->getPosition();
	Size size2 = sprite2->getContentSize();
	Rect spriteRect2 = Rect(position2.x, position2.y, size2.width,
			size2.height);
	return spriteRect1.intersectsRect(spriteRect2);
}

/*void GameScene::keyBackClicked(void) {
		CCLOG("\nKeyBack pressed\n");
		Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}*/



void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	cocos2d::CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

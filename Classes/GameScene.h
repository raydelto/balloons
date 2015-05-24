#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Sprites/Balloon.h"

#define DEFAULT_Y_SPEED 20
#define NUM_ABANICOS 10
#define NUM_RAMAS 7
#define BALLOON_IS_MOVING 1983 //valor arbitrario sin rigor alguno que representa una constante para saber el balón está siendo movido por un abanico
#define FAN_BLOWED 1984 //valor arbitrario sin rigor alguno que representa una constante para saber el abanico ya sopló

USING_NS_CC;
class GameScene : public cocos2d::Layer
{
public:
    virtual bool init();  
	GameScene();
    static cocos2d::Scene* scene();
    void menuCloseCallback(Ref* pSender);
	void menuRestartCallback(CCObject* pSender);
	static cocos2d::Scene* createScene();
    CREATE_FUNC(GameScene);
    
private:
    Sprite* m_background;
    Balloon* m_balloon;
	CCSize m_winSize;
	Sprite* m_btnInflar;
	Sprite* m_btnDesinflar;
	cocos2d::Vector<cocos2d::Sprite*> abanicos;
	cocos2d::Vector<cocos2d::Sprite*> ramas;
	bool initialized;
    bool m_gameOver;	
	bool m_won;	
    void updateGame(float dt);
	void updateViento(float dt);
	void scrollScene(float dt);
	void scrollBaloon(float dt);
	void scroll(Sprite* sprite, float dt, int direction);
	void initButtons();
	void initAbanicos();
	void initCloseMenu();
	void initBalloon();
	void initRamas();
	void initRestartMenu();
	void initBackground();	
	void checkCollisions();
	bool collisions(Rect &rect, Sprite* sprite);
	bool collisions(Sprite* sprite1,	Point* point);
	bool collisions(Sprite* sprite1, Sprite* sprite2);
	void inflarGlobo(float dt);
	void desinflarGlobo(float dt);
	void initBackButtonListener();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void initTouch();
	
	void balloonMoveFinished(Node* sender);
    bool ccTouchesBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void ccTouchesEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void showMessage(const char* message);


	
protected:
   // void keyBackClicked(void);
};



#endif // __GAME_SCENE_H__

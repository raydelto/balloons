#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "../Utilities/ns.h"
#include "Common/SCScene.h"
#include "Sprites/Balloon.h"
#include "Backgrounds/Simple.h"
#define DEFAULT_Y_SPEED 20
#define NUM_ABANICOS 10
#define NUM_RAMAS 7
#define BALLOON_IS_MOVING 1983 //valor arbitrario sin rigor alguno que representa una constante para saber el balón está siendo movido por un abanico
#define FAN_BLOWED 1984 //valor arbitrario sin rigor alguno que representa una constante para saber el abanico ya sopló
USING_NS_CATS;

NS_CATS_BEGIN

class GameScene : public SCScene
{
public:
    virtual bool init();  
	GameScene();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(GameScene);
    
private:
	Simple* m_background;
    Balloon* m_balloon;	
	CCSize m_winSize;
	CCSprite* m_btnInflar;
	CCSprite* m_btnDesinflar;
	CCArray* abanicos;
	CCArray* ramas;
    bool m_gameOver;	
	bool m_won;	
    void updateGame(float dt);
	void updateViento(float dt);
	void scrollScene(float dt);
	void scrollBaloon(float dt);
	void scroll(CCSprite* sprite, float dt, int direction);
	void initButtons();
	void initAbanicos();
	void initCloseMenu();
	void initBalloon();
	void initRamas();
	void initBackground();	
	void checkCollisions();
	bool collisions(CCRect &rect, CCSprite* sprite);
	bool collisions(CCSprite* sprite1,	CCPoint* point);
	bool collisions(CCSprite* sprite1,	CCSprite* sprite2);
	void inflarGlobo(float dt);
	void desinflarGlobo(float dt);
	void balloonMoveFinished(CCNode* sender);
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
	void showMessage(const char* message);


	
protected:
    void keyBackClicked(void);
};

NS_CATS_END

#endif // __GAME_SCENE_H__

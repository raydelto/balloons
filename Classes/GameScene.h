#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "../Utilities/ns.h"
#include "Common/SCScene.h"
#include "Sprites/Balloon.h"
#include "Backgrounds/Simple.h"
#define DEFAULT_Y_SPEED 20
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
    bool m_gameOver;	
    void updateGame(float dt);
	void scrollScene(float dt);
	void scrollBaloon(float dt);
	void scroll(CCSprite* sprite, float dt, int direction);
	void initButtons();
	bool collisions(cocos2d::CCSprite* sprite, cocos2d::CCPoint* point);
	bool collisions(cocos2d::CCSprite* sprite1,	cocos2d::CCSprite* sprite2);
	void inflarGlobo(float dt);
	void desinflarGlobo(float dt);
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);


	
protected:
    void keyBackClicked(void);
};

NS_CATS_END

#endif // __GAME_SCENE_H__

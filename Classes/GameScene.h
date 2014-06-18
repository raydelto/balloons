#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "../Utilities/ns.h"
#include "Common/SCScene.h"
#include "Sprites/Balloon.h"

USING_NS_CATS;

NS_CATS_BEGIN

class GameScene : public SCScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    
private:
    Balloon* m_balloon;
    bool m_gameOver;
    void updateGame(float dt);
protected:
    void keyBackClicked(void);
};

NS_CATS_END

#endif // __GAME_SCENE_H__

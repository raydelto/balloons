/*
 * Balloon.cpp
 *
 *      Author: eburgos
 */

#include "Balloon.h"
#include "../Common/SCSprite.h"
#include "SimpleAudioEngine.h"

Balloon::Balloon() {

}

Balloon::~Balloon() {

}

Balloon* Balloon::createWithFile(const char* pszFileName) {
	Balloon* balloon = new Balloon();
	if (balloon && balloon->initWithFile(pszFileName)) {
		balloon->autorelease();
		return balloon;
	}
	cocos2d::CCLog("Error creating Balloon with file name %s", pszFileName);
	CC_SAFE_DELETE(balloon);
	return NULL;
}


Balloon* Balloon::createWithTexture(cocos2d::CCTexture2D *pTexture){
	Balloon *balloon = new Balloon();
    if (balloon && balloon->initWithTexture(pTexture))
    {
        balloon->autorelease();
        return balloon;
    }
    cocos2d::CCLog("Error creating Balloon with Texture");
    CC_SAFE_DELETE(balloon);
    return NULL;
}

void explode(Balloon* balloon) {
    //this->unschedule(schedule_selector(JumpingGame::updateGame));
    //stopAllActions();
	//Evitando que la m�sica se detenga
    /*CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();*/
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/pop.wav", false);
//    GameOverScene *pScene = GameOverScene::create();
//    char scoreText[128];
//    sprintf(scoreText, "%d", m_playerScore);
//    pScene->getLayer()->getLabel()->setString(scoreText);
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,pScene));
    
    
    //CCDirector::sharedDirector()->replaceScene(pScene);
    return;
}


void Balloon::SCUpdate(float dt) {
	this->beforeUpdate(dt);
    this->m_X += this->m_speedX * dt;
    this->m_Y += this->m_speedY * dt;
    float x = this->m_X;
    float y = this->m_Y;
    this->setPosition(ccp(x, y));
	this->afterUpdate(dt);
}

void Balloon::afterUpdate(float dt) {
	//Raydelto: Coment� este logs, ya que escribir un log es una operaci�n costosa, desdocumenta solo si quieres probar algo espec�fico.
    //CCLog("%f", this->m_Y);
    if (this->m_Y > 600) {
        explode(this);
        this->setXY(this->m_X, 0);
    }
}




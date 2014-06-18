/*
 * SCSprite.cpp
 *
 *      Author: eburgos
 */

#include "./SCSprite.h"
#include "./SCScene.h"

SCSprite::SCSprite() {
    this->m_X = 0;
    this->m_Y = 0;
    this->m_speedX = 0;
    this->m_speedY = 0;
}

SCSprite::~SCSprite() {

}

void SCSprite::setXY(float x, float y) {
    this->m_X = x;
    this->m_Y = y;
}

void SCSprite::setSpeedX(float speed) {
    this->m_speedX = speed;
}

void SCSprite::setSpeedY(float speed) {
    this->m_speedY = speed;
}

void SCSprite::beforeUpdate(float dt) {
}

void SCSprite::afterUpdate(float dt) {
}

void SCSprite::SCUpdate(float dt) {
	this->beforeUpdate(dt);
    this->m_X += this->m_speedX * dt;
    this->m_Y += this->m_speedY * dt;
    float x = this->m_X;
    float y = this->m_Y;
    this->setPosition(ccp(x, y));
	this->afterUpdate(dt);
}
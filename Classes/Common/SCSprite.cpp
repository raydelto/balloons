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
	//Ahora mismo está vacío, anteriormente todos los SCPrites iban a subir, comportamiento que solo tendría sentido con el globo
}
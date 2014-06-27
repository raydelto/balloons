/*
 * SCScene.cpp
 *
 *      Author: eburgos
 */

#include "SCScene.h"

SCScene::SCScene() {
    this->m_elements = new CCArray();
}

SCScene::~SCScene() {

}

void SCScene::updating() {
}

void SCScene::addObject(SCSprite* o) {
    this->m_elements->addObject(o);
}
/*
bool SCScene::init() {
	//Evitando tener más de un schedule para no perder sincronización del juego.
    this->schedule(schedule_selector(SCScene::SCUpdate));
    return true;
}
*/
void SCScene::SCUpdate(float dt) {
    this->updating();
    CCArray* arr = this->m_elements;
    CCObject* sprite;
    CCARRAY_FOREACH(arr, sprite)
    {
        SCSprite* s = (SCSprite*) sprite;
        s->SCUpdate(dt);
    }
}
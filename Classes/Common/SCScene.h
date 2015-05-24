/*
 * SCScene.h
 *
 *      Author: eburgos
 */

#ifndef SCSCENE_H_
#define SCSCENE_H_

#include <cocos2d.h>
#include "../../Utilities/ns.h"

#include "./SCSprite.h"

USING_NS_CATS;

NS_CATS_BEGIN

class SCScene: public cocos2d::Layer {
public:
	SCScene();
        virtual void SCUpdate(float dt);
	virtual ~SCScene();
        //virtual bool init();
protected:
    virtual void updating();
    void addObject(SCSprite* o);
    CCArray* m_elements;

};

NS_CATS_END

#endif /* SCSCENE_H_ */

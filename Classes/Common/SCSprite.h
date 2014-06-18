/*
 * SCSprite.h
 *
 *      Author: eburgos
 */

#ifndef SCSPRITE_H_
#define SCSPRITE_H_

#include <cocos2d.h>
#include "../../Utilities/ns.h"

USING_NS_CATS;

NS_CATS_BEGIN

class SCSprite: public cocos2d::CCSprite {
public:
	SCSprite();
        virtual void SCUpdate(float dt);
		virtual void beforeUpdate(float dt);
		virtual void afterUpdate(float dt);
	virtual ~SCSprite();
        virtual void setXY(float x, float y);
        virtual void setSpeedX(float speed);
        virtual void setSpeedY(float speed);
protected:
    float m_X;
    float m_Y;
    float m_speedX;
    float m_speedY;
};

NS_CATS_END

#endif /* SCSPRITE_H_ */

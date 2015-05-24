/*
 * SCSprite.h
 *
 *      Author: eburgos
 */

#ifndef SCSPRITE_H_
#define SCSPRITE_H_

#include <cocos2d.h>


USING_NS_CC;


class SCSprite: public Sprite {
public:
	SCSprite();
        virtual void SCUpdate(float dt);
		virtual void beforeUpdate(float dt);
		virtual void afterUpdate(float dt);
	virtual ~SCSprite();
        virtual void setXY(float x, float y);
        virtual void setSpeedX(float speed);
        virtual void setSpeedY(float speed);
	    virtual float getSpeedX();
        virtual float getSpeedY();

protected:
    float m_X;
    float m_Y;
    float m_speedX;
    float m_speedY;
};


#endif /* SCSPRITE_H_ */

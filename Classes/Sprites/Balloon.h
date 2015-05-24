/*
 * Balloon.h
 *
 *      Author: eburgos
 */

#ifndef BALLOON_H_
#define BALLOON_H_

#include <cocos2d.h>
#include "../Common/SCSprite.h"

USING_NS_CC;
class Balloon: public SCSprite {
public:

	Balloon();
	virtual ~Balloon();
    static Balloon* createWithFile(const char * pszFileName);
    static Balloon* createWithTexture(cocos2d::CCTexture2D *pTexture);
	virtual void SCUpdate(float dt);
	void afterUpdate(float dt);
    
    
};



#endif /* BALLOON_H_ */

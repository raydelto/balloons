/*
 * Balloon.h
 *
 *      Author: eburgos
 */

#ifndef BALLOON_H_
#define BALLOON_H_

#include <cocos2d.h>
#include "../../Utilities/ns.h"
#include "../Common/SCSprite.h"

USING_NS_CATS;

NS_CATS_BEGIN

class Balloon: public SCSprite {
public:

	Balloon();
	virtual ~Balloon();
    static Balloon* createWithFile(const char * pszFileName);
    static Balloon* createWithTexture(cocos2d::CCTexture2D *pTexture);
	virtual void SCUpdate(float dt);
	void afterUpdate(float dt);
    
protected:
    
};

NS_CATS_END

#endif /* BALLOON_H_ */

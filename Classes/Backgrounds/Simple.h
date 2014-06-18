/*
 * Simple.h
 *
 *      Author: eburgos
 */

#ifndef BACKGROUND_SIMPLE_H_
#define BACKGROUND_SIMPLE_H_

#include <cocos2d.h>
#include "../../Utilities/ns.h"
#include "../Common/SCSprite.h"

USING_NS_CATS;

NS_CATS_BEGIN
        
class Simple: public SCSprite {
public:

	Simple();
	virtual ~Simple();
    static Simple* createWithFile(const char * pszFileName);
    static Simple* createWithTexture(cocos2d::CCTexture2D *pTexture);
    
protected:
};

NS_CATS_END

#endif /* BACKGROUND_SIMPLE_H_ */
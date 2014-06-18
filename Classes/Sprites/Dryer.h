/*
 * Dryer.h
 *
 *      Author: eburgos
 */

#ifndef DRYER_H_
#define DRYER_H_

#include <cocos2d.h>
#include "../../Utilities/ns.h"
#include "../Common/SCSprite.h"

USING_NS_CATS;

NS_CATS_BEGIN

class Dryer: public SCSprite {
public:

	Dryer();
	virtual ~Dryer();
    static Dryer* createWithFile(const char * pszFileName);
    static Dryer* createWithTexture(cocos2d::CCTexture2D *pTexture);
    
protected:
    
};

NS_CATS_END

#endif /* DRYER_H_ */

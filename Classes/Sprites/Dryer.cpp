/*
 * Dryer.cpp
 *
 *      Author: eburgos
 */

#include "Dryer.h"
#include "../Common/SCSprite.h"

Dryer::Dryer() {

}

Dryer::~Dryer() {

}

Dryer* Dryer::createWithFile(const char* pszFileName) {
	Dryer* dryer = new Dryer();
	if (dryer && dryer->initWithFile(pszFileName)) {
		dryer->autorelease();
		return dryer;
	}
	cocos2d::CCLog("Error creating Dryer with file name %s", pszFileName);
	CC_SAFE_DELETE(dryer);
	return NULL;
}


Dryer* Dryer::createWithTexture(cocos2d::CCTexture2D *pTexture){
	Dryer *dryer = new Dryer();
    if (dryer && dryer->initWithTexture(pTexture))
    {
        dryer->autorelease();
        return dryer;
    }
    cocos2d::CCLog("Error creating Dryer with Texture");
    CC_SAFE_DELETE(dryer);
    return NULL;
}




/*
 * Simple.cpp
 *
 *      Author: eburgos
 */

#include "Simple.h"

Simple::Simple() {
}

Simple::~Simple() {

}

Simple* Simple::createWithFile(const char* pszFileName) {
	Simple* simple = new Simple();
	if (simple && simple->initWithFile(pszFileName)) {
		simple->autorelease();
		return simple;
	}
	cocos2d::CCLog("Error creating Simple background with file name %s", pszFileName);
	CC_SAFE_DELETE(simple);
	return NULL;
}


Simple* Simple::createWithTexture(CCTexture2D *pTexture){
	Simple *simple = new Simple();
    if (simple && simple->initWithTexture(pTexture))
    {
        simple->autorelease();
        return simple;
    }
    cocos2d::CCLog("Error creating Simple background with Texture");
    CC_SAFE_DELETE(simple);
    return NULL;
}




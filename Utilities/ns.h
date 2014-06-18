#ifndef __CATS_NS_H__
#define __CATS_NS_H__

#define NS_CATS cocos2d

// namespace cocos2d {}
#ifdef __cplusplus
    #define NS_CATS_BEGIN                     namespace cocos2d {
    #define NS_CATS_END                       }
    #define USING_NS_CATS                     using namespace cocos2d
#else
    #define NS_CATS_BEGIN 
    #define NS_CATS_END 
    #define USING_NS_CATS 
#endif 

NS_CATS_BEGIN
NS_CATS_END

#endif // __CATS_NS_H__

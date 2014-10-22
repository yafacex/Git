//
//  CallbackActNode.h
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestSpirit__CallbackActNode__
#define __TestSpirit__CallbackActNode__

#include <boost/function.hpp>
#include "BaseActNode.h"
using namespace boost;
class CallbackActNode:public BaseActNode{
public:
    typedef function<bool()> ConditionalFunc;
    CallbackActNode(ConditionalFunc func){
        this->mFunc = func;
    };
    virtual ACT_STATUS execute();
protected:
    ConditionalFunc mFunc;
};
#endif /* defined(__TestSpirit__CallbackActNode__) */

//
//  ConditionActNode.h
//  BeTreeTest
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __BeTreeTest__ConditionActNode__
#define __BeTreeTest__ConditionActNode__
#include "BaseActNode.h"
#include <boost/function.hpp>
using namespace boost;
class ConditionActNode:public BaseActNode{
public:
    typedef function<bool()> ConditionalFunc;
    ConditionActNode(ConditionalFunc func){
        this->mFunc = func;
    };
    virtual ACT_STATUS execute();
protected:
    ConditionalFunc mFunc;
};
#endif /* defined(__BeTreeTest__ConditionActNode__) */

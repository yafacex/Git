//
//  CallbackActNode.cpp
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "CallbackActNode.h"

ACT_STATUS CallbackActNode::execute(){
    mFunc();
    return AS_Success;
}
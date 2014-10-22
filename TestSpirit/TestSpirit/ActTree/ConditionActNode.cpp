//
//  ConditionActNode.cpp
//  BeTreeTest
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "ConditionActNode.h"

ACT_STATUS ConditionActNode::execute(){
    if (mFunc() == true) {
        return AS_Success;
    }else{
        return AS_Failure;
    }
}
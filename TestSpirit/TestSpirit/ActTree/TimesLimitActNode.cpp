//
//  TimesLimitActNode.cpp
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "TimesLimitActNode.h"
#include <assert.h>
#include <iostream>
TimesLimitActNode::TimesLimitActNode(int times){
    mTimes = times;
    reset();
}
void TimesLimitActNode::addChild(BaseActNode* child){
    if(mChildren.size() == 0){
        mChildren.push_back(child);
    }else{
        assert(false);
        std::cout << "Skill Act Root Can Only Has One Child!" << std::endl;
    };
};
ACT_STATUS TimesLimitActNode::execute(){
    if (mCnter == mTimes) {
        return AS_Success;
    }else{
        if (mChildren.size() == 1) {
            ACT_STATUS st = mChildren[0]->execute();
            if (AS_Success == st || AS_Failure == st) {
                mChildren[0]->reset();
            }
            return AS_Running;
        }else{
            return AS_Failure;
        }
    }
}
void TimesLimitActNode::reset(){
    mCnter = 0;
}
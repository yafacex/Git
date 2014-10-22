//
//  TimesLimitActNode.h
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestSpirit__TimesLimitActNode__
#define __TestSpirit__TimesLimitActNode__

#include "BaseActNode.h"

class TimesLimitActNode:public CompositeActNode{
public:
    TimesLimitActNode(int times);
    virtual void addChild(BaseActNode* child);
    virtual ACT_STATUS execute();
    virtual void reset();
protected:
    int mCnter;
    int mTimes;
};

#endif /* defined(__TestSpirit__TimesLimitActNode__) */

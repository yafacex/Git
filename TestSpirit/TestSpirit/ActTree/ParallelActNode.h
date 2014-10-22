//
//  ParallelActNode.h
//  BeTreeTest
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __BeTreeTest__ParallelActNode__
#define __BeTreeTest__ParallelActNode__

#include "BaseActNode.h"
#include <map>
using namespace std;
class ParallelActNode:public CompositeActNode{
public:
    enum SuccessCategory{
        Success_On_One,
        Success_On_All
    };
    enum FailureCategory{
        Failure_On_One,
        Failure_On_All
    };
    ParallelActNode(SuccessCategory suc,FailureCategory fail);
    virtual ACT_STATUS execute();
    map<BaseActNode*, ACT_STATUS> mStatusInfo;
    virtual void reset();
protected:
    SuccessCategory mSucCategory;
    FailureCategory mFailCategory;
};
#endif /* defined(__BeTreeTest__ParallelActNode__) */

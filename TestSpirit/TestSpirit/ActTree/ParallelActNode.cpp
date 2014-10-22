//
//  ParallelActNode.cpp
//  BeTreeTest
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "ParallelActNode.h"
#include <assert.h>

ACT_STATUS ParallelActNode::execute(){
    for (vector<BaseActNode*>::iterator itr = mChildren.begin();
         itr != mChildren.end(); ++itr) {
        if (mStatusInfo[*itr] == AS_Running) {
            ACT_STATUS st = (*itr)->execute();
            if (AS_Failure == st && Failure_On_One ==  mFailCategory) {
                return AS_Failure;
            }
            if (AS_Running != st) {
                mStatusInfo[*itr] = st;
            }
        }
    }
    
    bool bOneSuc = true,bAllFail = true,bAllSuc = true;
    
    for (map<BaseActNode*, ACT_STATUS>::iterator itr = mStatusInfo.begin();
         itr != mStatusInfo.end(); ++itr) {
        switch ((*itr).second) {
            case AS_Running:{
                bAllFail = bAllSuc = false;
            }
                break;
            case AS_Failure:{
                bAllSuc = false;
            }
                break;
            case AS_Success:{
                bAllFail = false;
            }
                break;
            default:
                break;
        }
    }
    
    if ((mSucCategory == Success_On_One && bOneSuc) ||
        (mSucCategory == Success_On_All && bAllSuc)) {
        return AS_Success;
    }
    if (mFailCategory == Failure_On_All && bAllFail) {
        return AS_Failure;
    }
    assert(false);
    return AS_Failure;
}
ParallelActNode::ParallelActNode(SuccessCategory suc,FailureCategory fail){
    mSucCategory = suc;
    mFailCategory = fail;
}
void ParallelActNode::reset(){
    CompositeActNode::reset();
    for (map<BaseActNode*, ACT_STATUS>::iterator itr = mStatusInfo.begin();
         itr != mStatusInfo.end(); ++itr) {
        (*itr).second = AS_Running;
    }
}
//
//  FilterActNode.h
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestSpirit__FilterActNode__
#define __TestSpirit__FilterActNode__
#include "../ActTree/BaseActNode.h"
#include "TestH.h"
#include "SkillCfg.h"
using namespace Skill;
class FilterActNode:public BaseActNode{
public:
    FilterActNode(CCCharacterVector* result,ClusterFeature* feature,CCGameCharacter* owner):mResult(NULL){
        mResult = result;
        mFeature = feature;
        mOwner = owner;
    };
    
    virtual ACT_STATUS execute();
    
protected:
    CCCharacterVector* mResult;
    ClusterFeature* mFeature;
    CCGameCharacter* mOwner;
};
#endif /* defined(__TestSpirit__FilterActNode__) */

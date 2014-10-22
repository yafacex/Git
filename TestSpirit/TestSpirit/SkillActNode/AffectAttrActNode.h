//
//  AffectAttrActNode.h
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestSpirit__AffectAttrActNode__
#define __TestSpirit__AffectAttrActNode__

#include "TestH.h"
#include "SkillCfg.h"
#include "BaseActNode.h"
class AffectAttrActNode{
public:
    AffectAttrActNode(CCCharacterVector* result,Skill::DataRule* dataRule,CCGameCharacter* owner);
    
    virtual ACT_STATUS execute();
protected:
    CCCharacterVector* mResult;
    Skill::DataRule* mDataRule;
    CCGameCharacter* mOwner;
};
#endif /* defined(__TestSpirit__AffectAttrActNode__) */

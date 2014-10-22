//
//  SkillActRoot.h
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestSpirit__SkillActRoot__
#define __TestSpirit__SkillActRoot__

#include "BaseActNode.h"

class SkillActRoot:public CompositeActNode{
public:
    virtual void addChild(BaseActNode* child);
};
#endif /* defined(__TestSpirit__SkillActRoot__) */

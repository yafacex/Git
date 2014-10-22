//
//  SkillActRoot.cpp
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "SkillActRoot.h"
#include <iostream>
#include <assert.h>
void SkillActRoot::addChild(BaseActNode* child){
    if(mChildren.size() == 0){
        mChildren.push_back(child);
    }else{
        assert(false);
        std::cout << "Skill Act Root Can Only Has One Child!" << std::endl;
    };
};
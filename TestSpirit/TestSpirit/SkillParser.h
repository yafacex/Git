//
//  SkillParser.h
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestSpirit__SkillParser__
#define __TestSpirit__SkillParser__

#include "SkillCfg.h"
class BaseActNode;
class SkillParser{
public:
    void parse(vector<Skill::SkillCfg::SkillDb*>* skilldbs);
    BaseActNode* parseOne(Skill::SkillCfg::SkillDb* skilldb);
};
#endif /* defined(__TestSpirit__SkillParser__) */

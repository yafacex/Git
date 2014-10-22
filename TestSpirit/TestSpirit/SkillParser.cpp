//
//  SkillParser.cpp
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "SkillParser.h"
#include "SequenceActNode.h"
#include "ParallelActNode.h"
#include "BaseActNode.h"
#include "SkillActNode/SkillActRoot.h"
#include "CallbackActNode.h"
using namespace std;
void SkillParser::parse(vector<Skill::SkillCfg::SkillDb*>* skilldbs){
    SkillActRoot* root = new SkillActRoot();
    ParallelActNode* main = new ParallelActNode(ParallelActNode::Success_On_All,
                                                   ParallelActNode::Failure_On_All);
    root->CompositeActNode::addChild(main);
    for (vector<Skill::SkillCfg::SkillDb*>::iterator itr = skilldbs->begin();
         itr != skilldbs->end(); ++itr) {
        main->addChild(parseOne(*itr));
    }
}
BaseActNode* SkillParser::parseOne(Skill::SkillCfg::SkillDb* skilldb){
    
    SequenceActNode* LogicNode = new SequenceActNode();
    
    if (skilldb->waitForSec > 0) {
        SuccessAfterSec* waitT = new SuccessAfterSec(skilldb->waitForSec);
        LogicNode->addChild(waitT);
    }
    
    
    switch(skilldb->timerRule->timer){
        case Skill::every_n_sec_delay:{
            SuccessAfterSec* wait = new SuccessAfterSec(skilldb->timerRule->sec);
//            CallbackActNode* callback = new CallbackActNode();
        }
            break;
        case Skill::rightnow:{
            
        }
            break;
    }
    
    return LogicNode;
}
//
//  SkillCfg.cpp
//  TestSpirit
//
//  Created by yafacex on 14-8-5.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "SkillCfg.h"
#include "VM.h"
#include "SkillParser.h"

#include "ActTree/SequenceActNode.h"
using namespace Skill;
void SkillCfg::createCluster(){
    mCurCluster = new ClusterFeature();
};
void SkillCfg::setClusterRelationShip(int alienOrEnemy){
    mCurCluster->addFeature((Feature)alienOrEnemy,0);
};
void SkillCfg::setClusterHeroBuilingSoldier(int whatKind){
    mCurCluster->addFeature((Feature)whatKind,0);
};
void SkillCfg::setClusterRange(int range,float grid){
    mCurCluster->addFeature((Feature)range,grid);
};
void SkillCfg::setClusterHpRange(int range){
    mCurCluster->addFeature((Feature)range, 0);
};

void SkillCfg::createDataRule(){
    mCurDataRule = new DataRule();
};
void SkillCfg::setDataRuleTarget(int attr){
    mCurDataRule->attr = (Attr)attr;
};
void SkillCfg::setDataRuleOp(int op){
    mCurDataRule->op = (OP)op;
}
void SkillCfg::setDataRuleDatas(string key){
    vector<float>* datas = VM::getInstance()->getTable()->getDatasByAttr(key);
    mCurDataRule->dataSet = datas;
}

void SkillCfg::createTimerRule(){
    mCurTimerRule = new TimerRule();
};
void SkillCfg::setTimerRuleRightNow(){
    mCurTimerRule->timer = rightnow;
    mCurTimerRule->sec = 0;
    mCurTimerRule->times = 1;
}
void SkillCfg::setTimerRuleCycle(int times,float sec){
    mCurTimerRule->timer = every_n_sec_delay;
    mCurTimerRule->sec = sec;
    mCurTimerRule->times = times;
}
void SkillCfg::setWaitForSec(float sec){
    mWaitForSec = sec;
}
void SkillCfg::skillCombine(){
    SkillDb* db = new SkillDb();
    db->clusterFeature = mCurCluster;
    db->dataRule = mCurDataRule;
    db->timerRule = mCurTimerRule;
    db->waitForSec = mWaitForSec;
    mSkillDbs.push_back(db);
};

void SkillCfg::skillParse(){
    SkillParser parser;
    parser.parse(&mSkillDbs);
}
//
//  BuiltInFunc.cpp
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "BuiltInFunc.h"
#include "VM.h"
#include <boost/bind.hpp>

void BuiltInFunc::createSkillCfgByDescriptionName(){
    string name = VM::getInstance()->getDescription()->name;
}
void BuiltInFunc::addSkillFeatureRange(int feature){

}
void BuiltInFunc::addSkillFeatureHp(int feature){

}
void BuiltInFunc::addSkillTargetAttr(int attr){

}
void BuiltInFunc::addSkillOp(int op){
    
}

void BuiltInFunc::doCall(string funcName,ParamTables& paramTables){
    if (paramTables.size() == 1) {
        switch (paramTables.at(0)->data.tag) {
            case Real:{
                if (m_void_float1_funcs.find(funcName) == m_void_float1_funcs.end()) {
                    cout << "No Func Exist => " << funcName  << endl;
                    assert(false);
                }
                m_void_float1_funcs[funcName](paramTables.at(0)->data.value.real);
            }
                break;
            case Int:{
                if (m_void_int1_funcs.find(funcName) == m_void_int1_funcs.end()) {
                    cout << "No Func Exist => " << funcName  << endl;
                    assert(false);
                }
                m_void_int1_funcs[funcName](paramTables.at(0)->data.value.integer);
            }
                break;
            case String:{
                if (m_void_string1_funcs.find(funcName) == m_void_string1_funcs.end()) {
                    cout << "No Func Exist => " << funcName  << endl;
                    assert(false);
                }
                string str(paramTables.at(0)->data.value.str);
                m_void_string1_funcs[funcName](str);
            }
            default:
                break;
        }
    }else if(paramTables.size() == 2){
        if (m_void_int1_float1_funcs.find(funcName) == m_void_int1_float1_funcs.end()) {
            cout << "No Func Exist => " << funcName  << endl;
            assert(false);
        }
        m_void_int1_float1_funcs[funcName](paramTables.at(0)->data.getInt(),
                                           paramTables.at(1)->data.getReal());
    }else if(paramTables.size() == 0){
        if (m_void_void_funcs.find(funcName) == m_void_void_funcs.end()) {
            cout << "No Func Exist => " << funcName  << endl;
            assert(false);
        }
        m_void_void_funcs[funcName]();
    }else{
        cout<< "Not Support More than one Param Script" <<endl;
        assert(false);
    }
}
void BuiltInFunc::registSkillFuncs(Skill::SkillCfg* cfg){
    regist_void_void("$createCluster", boost::bind(&Skill::SkillCfg::createCluster,cfg));
    regist_void_int1("$setClusterRelationShip", boost::bind(&Skill::SkillCfg::setClusterRelationShip,cfg,_1));
    regist_void_int1("$setClusterHeroBuilingSoldier", boost::bind(&Skill::SkillCfg::setClusterHeroBuilingSoldier,cfg,_1));
    regist_void_int1_float1("$setClusterRange", boost::bind(&Skill::SkillCfg::setClusterRange,cfg,_1,_2));
    
    regist_void_int1("$setClusterHpRange", boost::bind(&Skill::SkillCfg::setClusterHpRange,cfg,_1));
    regist_void_void("$createDataRule", boost::bind(&Skill::SkillCfg::createDataRule,cfg));
    regist_void_int1("$setDataRuleTarget", boost::bind(&Skill::SkillCfg::setDataRuleTarget,cfg,_1));
    regist_void_int1("$setDataRuleOp", boost::bind(&Skill::SkillCfg::setDataRuleOp,cfg,_1));
    regist_void_string1("$setDataRuleDatas", boost::bind(&Skill::SkillCfg::setDataRuleDatas,cfg,_1));
    
    regist_void_void("$createTimerRule", boost::bind(&Skill::SkillCfg::createTimerRule,cfg));
    regist_void_void("$setTimerRuleRightNow", boost::bind(&Skill::SkillCfg::setTimerRuleRightNow,cfg));
    regist_void_int1_float1("$setTimerRuleCycle", boost::bind(&Skill::SkillCfg::setTimerRuleCycle,cfg,_1,_2));
    
    regist_void_float1("$setWaitForSec", boost::bind(&Skill::SkillCfg::setWaitForSec,cfg,_1));
    
    regist_void_void("$skillCombine", boost::bind(&Skill::SkillCfg::skillCombine,cfg));
    
    regist_void_void("$skillParse", boost::bind(&Skill::SkillCfg::skillParse,cfg));
    
}
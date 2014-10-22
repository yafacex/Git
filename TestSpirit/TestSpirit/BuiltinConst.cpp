//
//  BuiltinConst.cpp
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "BuiltinConst.h"
#include "SkillCfg.h"

VariantTable* getVT_Int(string name,int value){
    VariantTable* t = new VariantTable();
    t->variantName = name;
    t->data.tag = Int;
    t->data.value.integer = value;
    return t;
};
VariantTable* getVT_Real(string name,float value){
    VariantTable* t = new VariantTable();
    t->variantName = name;
    t->data.tag = Real;
    t->data.value.real = value;
    return t;
};

void BuiltinConst::initBuiltinConst(VariantTables& variantTables){
    //skill feature
    variantTables["@nearest"]=getVT_Int("@nearest",Skill::nearest);
    variantTables["@farest"]=getVT_Int("@farest",Skill::farest);
    variantTables["@in"]=getVT_Int("@in",Skill::in);
    variantTables["@out"]=getVT_Int("@out",Skill::out);
    
    variantTables["@enemy"]=getVT_Int("@enemy",Skill::enemy);
    variantTables["@alien"]=getVT_Int("@alien",Skill::alien);
    
    variantTables["@soldier"]=getVT_Int("@enemy",Skill::soldier);
    variantTables["@hero"]=getVT_Int("@alien",Skill::hero);
    variantTables["@character"]=getVT_Int("@alien",Skill::character);
    variantTables["@me"]=getVT_Int("@me",Skill::character);
    
    variantTables["@leastHp"]=getVT_Int("@leastHp",Skill::leastHp);
    variantTables["@mostHp"]=getVT_Int("@mostHp",Skill::mostHp);
    
    variantTables["@hp"]=getVT_Int("@hp",Skill::hp);
    variantTables["@movespd"]=getVT_Int("@movespd",Skill::movespd);
    variantTables["@attackspd"]=getVT_Int("@attackspd",Skill::attackspd);
    
    variantTables["@mul"]=getVT_Int("@mul",Skill::mul);
    variantTables["@add"]=getVT_Int("@add",Skill::add);
    
    variantTables["@every_n_sec_delay"]=getVT_Int("@every_n_sec_delay",Skill::every_n_sec_delay);
    variantTables["@rightnow"]=getVT_Int("@rightnow",Skill::rightnow);
};
//
//  BuiltInFunc.h
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestSpirit__BuiltInFunc__
#define __TestSpirit__BuiltInFunc__
#include <boost/function.hpp>
#include <deque>
#include <boost/unordered_map.hpp>
#include "TypeDef.h"
#include "SkillCfg.h"
using namespace boost;
using namespace std;
using namespace VmNs;
#include <iostream>
class BuiltInFunc{
public:
    typedef function<void()> Func_void_void;
    typedef function<void(int)> Func_void_int1;
    typedef function<void(float)> Func_void_float1;
    typedef function<void(string)> Func_void_string1;
    typedef function<void(int,float)> Func_void_int1_float1;
    
    void doCall(string funcName,ParamTables& paramTables);
    void regist_void_float1(string funcName,Func_void_float1 func){
        m_void_float1_funcs[funcName] = func;
    };
    void regist_void_string1(string funcName,Func_void_string1 func){
        m_void_string1_funcs[funcName] = func;
    }
    void regist_void_int1(string funcName,Func_void_int1 func){
        m_void_int1_funcs[funcName] = func;
    }
    void regist_void_void(string funcName,Func_void_void func){
        m_void_void_funcs[funcName] = func;
    }
    void regist_void_int1_float1(string funcName,Func_void_int1_float1 func){
        m_void_int1_float1_funcs[funcName] = func;
    }
    unordered_map<string, Func_void_void> m_void_void_funcs;
    unordered_map<string, Func_void_int1> m_void_int1_funcs;
    unordered_map<string, Func_void_float1> m_void_float1_funcs;
    unordered_map<string, Func_void_string1> m_void_string1_funcs;
    unordered_map<string, Func_void_int1_float1> m_void_int1_float1_funcs;
public:
    /**
     Skill
     */
    
    void createSkillCfgByDescriptionName();
    void addSkillFeatureRange(int feature);
    void addSkillFeatureHp(int feature);
    void addSkillTargetAttr(int attr);
    void addSkillOp(int op);
public:
    void registSkillFuncs(Skill::SkillCfg* cfg);
};

#endif /* defined(__TestSpirit__BuiltInFunc__) */


//
//  VM.h
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestSpirit__VM__
#define __TestSpirit__VM__

#include <iostream>
#include <deque>
#include "ProgData.h"
#include <boost/unordered_map.hpp>
#include "TypeDef.h"
#include "BuiltInFunc.h"
#include "BuiltinConst.h"

#include <spirit/Spirit.h>

using Spirit::Rule;
using Spirit::Scanner;
using Spirit::Action;
using Spirit::Lexeme;
using Spirit::ch_p;
using Spirit::digit;
using Spirit::space;

using namespace Spirit;
using namespace std;
using namespace boost;
using namespace VmNs;

#define COMMON_ARGS char const* l,char const* r
#define DBG_CONTENT\
    std::string _str(l,r);\
    std::cout << "Content:"<<std::endl<<_str << std::endl << "End" << std::endl;
#define TRIM_STR\
    string str = string(l,r);\
    str.erase(str.find_last_not_of(" ") + 1);

class VM{
public:
    VM();
    static inline VM* getInstance(){
        static VM svm;
        return &svm;
    };
    
    void loadGrammar();
    bool bLoaded;
    void compile();
public:
    
    VariantTables variantTables;
    ParamTables paramTables;

public:
    //built in
    static bool bInitBuiltin;
    void initBuiltinConst();
    VariantTable* getBuiltinConst(string name);
    void initBuiltinFunc();
public:
    void VmParamVariant(COMMON_ARGS){
        DBG_CONTENT;
        TRIM_STR;
        
    };
    void VmParamConstBuildin(COMMON_ARGS){
        DBG_CONTENT;
        TRIM_STR;
        paramTables.push_back(getBuiltinConst(str));
    };
    void VmParamReal(COMMON_ARGS){
        DBG_CONTENT;
        TRIM_STR;
        float value = atof(str.c_str());
        ParamTable* param = new ParamTable();
        param->data.tag = VmNs::Real;
        param->data.value.real = value;
        paramTables.push_back(param);
    };
    void VmParamInteger(COMMON_ARGS){
        DBG_CONTENT;
        TRIM_STR;
        int value = atoi(str.c_str());
        ParamTable* param = new ParamTable();
        param->data.tag = VmNs::Int;
        param->data.value.integer = value;
        paramTables.push_back(param);
    };
    void VmParamString(COMMON_ARGS){
        DBG_CONTENT;
        string* str = new string(l,r);
        ParamTable* param = new ParamTable();
        param->data.tag = VmNs::String;
        param->data.value.str = str->c_str();
        paramTables.push_back(param);
    }
    void VmCallFunc(COMMON_ARGS){
        
    };
    void VmCallFuncBeginBuiltin(COMMON_ARGS){
        DBG_CONTENT;
        TRIM_STR
        curFuncName = str;
        curFuncType = Builtin;
        paramTables.clear();
    };
    void VmCallFuncEndBuiltin(COMMON_ARGS){
        DBG_CONTENT;
        TRIM_STR;
        switch (curFuncType) {
            case Builtin:
                callFuncs.doCall(curFuncName, paramTables);
                break;
            case Normal:
                cout << "Normal Func not Impl yet!" << endl;
                assert(false);
                break;
            default:
                break;
        }
    };
    string curFuncName;
    FuncType curFuncType;
    BuiltInFunc callFuncs;
    BuiltinConst consts;
public:
    void DescriptionName(COMMON_ARGS) {
        DBG_CONTENT;
        string str(l,r);
        m_description.name = str;
    }
    void DescriptionEffect(COMMON_ARGS){
        DBG_CONTENT;
        string str(l,r);
        m_description.effect = str;
    }
    void TableAttr(COMMON_ARGS){
        DBG_CONTENT;
        string str(l,r);
        m_table.startRecord(str);
    };
    void TableDataReal(COMMON_ARGS){
        DBG_CONTENT;
        string str(l,r);
        m_table.record(atof(str.c_str()));
    }
    void TableDataInt(COMMON_ARGS){
        DBG_CONTENT;
        string str(l,r);
        m_table.record(atof(str.c_str()));
    }
    
    Description * getDescription(){
        return &m_description;
    };
    Table * getTable(){
        return &m_table;
    };
protected:
    Description m_description;
    Table m_table;
    
    Rule<> Real,Integer,String;
    Rule<> AnyChar,BChar,Enter;
    //comment & description
    Rule<> Table,Description,Comment,CommentN,Table_,Description_;
    //function & variant
    Rule<> FunctionCall,Param,Params,FunctionName,ParamName,FunctionBuildin;
    Rule<> VariantName,ConstName;
    Rule<> Expr;
    
    Rule<> DeclareVariant;
    
    Rule<> RowTable;
};
#endif /* defined(__TestSpirit__VM__) */

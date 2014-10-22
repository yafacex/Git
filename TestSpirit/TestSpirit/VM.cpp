//
//  VM.cpp
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "VM.h"
#include <assert.h>
#include "SkillCfg.h"
#include <spirit/Spirit.h>
#include <boost/bind.hpp>
using namespace std;
using namespace VmNs;

using Spirit::Rule;
using Spirit::Scanner;
using Spirit::Action;
using Spirit::Lexeme;
using Spirit::ch_p;
using Spirit::digit;
using Spirit::space;

using namespace Spirit;

bool VM::bInitBuiltin = false;



VM::VM():bLoaded(false){
    if (!bInitBuiltin) {
        initBuiltinConst();
        initBuiltinFunc();
        bInitBuiltin = true;
    }
}

void VM::initBuiltinConst(){
    consts.initBuiltinConst(variantTables);
};
void VM::initBuiltinFunc(){
    Skill::SkillCfg* cfg =new Skill::SkillCfg();
    callFuncs.registSkillFuncs(cfg);
}
VariantTable* VM::getBuiltinConst(string name){
    VariantTableIterator itr = variantTables.find(name);
    if (itr != variantTables.end()) {
        return variantTables[name];
    }
    cout << "no built in Variant ["<< name<<"] exist!" << endl;
    assert(false);
    return NULL;
}
#define BindFunc(_V_)\
    [boost::bind(&VM::_V_,this,_1,_2)]
#define STR(_V_) StrLit<>(#_V_)

Rule<> Skill_;
void VM::loadGrammar(){
    //support
    
    if (bLoaded) {
        return;
    }
    bLoaded = true;
    /**
     Support
     */
	AnyChar = ChLit<>('\x9') | ChLit<>('\xA') | ChLit<>('\xD') | Spirit::Range<unsigned char>('\x20', '\xFF');
    BChar = Spirit::Range<unsigned char>(65, 90) | Spirit::Range<unsigned char>(97, 122);
    Enter = ch_p('\r') | ch_p('\n');
    
    Integer = Lexeme[ (!ch_p('-') >> +digit)];
    Real = Lexeme[!ch_p('-') >> +digit >> '.' >> +digit];
    String =  +BChar;
    
    ConstName = (ch_p('@')>>+BChar);
    /**
     Table
     */
    RowTable = Lexeme[ch_p('"') >> String BindFunc(TableAttr)>> ch_p('"')] >> ch_p('=') >>
    (
     (+Real BindFunc(TableDataReal)) |
     (+Integer BindFunc(TableDataInt))
     );
    Table_ = ch_p('{')>> (*RowTable) >> '}';
    Table = STR(Table) >> ch_p('=')>> Table_;
    
    /*
     Description
     */
    Description_ = ch_p('{') >>
    STR(Name)>> ':' >>Lexeme[(+BChar)BindFunc(DescriptionName) ]>>
    STR(Effect) >> ':'>>Lexeme[(+(AnyChar-'}')) ] >>
    '}';
    Description = STR(Description) >> '=' >> Description_;
    
    /*
     Comment
     just like c/c++
     */
    Comment = "/*" >> (*(AnyChar-'*'-'/')) >> "*/" ;
    CommentN = *Comment;
    
    /*
     Function & Declare & Expr
     */
    VariantName = +BChar;
    DeclareVariant = STR(var) >> STR(VariantName) >> ch_p('=') >> Expr;
    
    FunctionName =  (ch_p('$')>>(+BChar)) BindFunc(VmCallFuncBeginBuiltin);
    FunctionCall = FunctionName>>ch_p('(')>>Params>>ch_p(')') BindFunc(VmCallFuncEndBuiltin)>>+ch_p(';');
    
    ParamName = (+BChar) | ConstName BindFunc(VmParamConstBuildin);
    Param = ParamName |
    Real BindFunc(VmParamReal)|
    Integer BindFunc(VmParamInteger)|
    Lexeme[ch_p('"') >> String BindFunc(VmParamString)>> ch_p('"')];
    Params = !Param >> (*(ch_p(',')>>Param));
    
    Expr = Real | Integer | VariantName | FunctionCall |
    (VariantName>> ch_p('=') >> Real)|
    (VariantName>> ch_p('=') >> Integer) |
    (VariantName>> ch_p('=') >> FunctionCall);
    
    /**
     Skill
     */
    Skill_ = CommentN>>Description >>CommentN>> Table >>*(CommentN>> Expr)>>CommentN;
    
    
    
}
static int fin = 0;
void VM::compile(){
    FILE* fp = fopen("haha.skill", "r");
    fseek(fp,0L,SEEK_END);
    long size = ftell(fp);
    if (size > 1000) {
        std::cout << "Skill File is Too Long" << std::endl;
        return;
    }
    char * fc = new char[size];
    memset(fc, 0, size);
    fseek(fp,0L,SEEK_SET);
    fread(fc, sizeof(char), size, fp);
    string str(fc);
    std::cout << "File Content:" << std::endl << str <<std::endl;
    Spirit::Scanner<> scan(fc,Spirit::space);
    if (Skill_.Parse(scan) ){//&& !*scan) {
        std::cout<<"Compile Success!"<<std::endl;
    }else{
        std::cout<<"Compile Failure!"<<fin<<std::endl;
        assert(false);
    }
    ++fin;
}
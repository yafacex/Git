//
//  TypeDef.h
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestSpirit_TypeDef_h
#define TestSpirit_TypeDef_h
#include <boost/unordered_map.hpp>
#include <deque>
using namespace std;
using namespace boost;
namespace VmNs {
    enum FuncType{
        Normal,
        Builtin
    };
    enum TypeTag{
        Real,
        Int,
        String
    };
    union TypeVal{
        float real;
        int integer;
        const char* str;
    };
    typedef struct DataType_{
        TypeTag tag;
        TypeVal value;
    public:
        float getReal(){
            if(tag == Real){
                return value.real;
            }else{
                return (float)value.integer;
            }
        }
        int getInt(){
            if(tag == Real){
                return (int)value.real;
            }else{
                return value.integer;
            }
        }
    }DataType;
    
    typedef struct VariantTable_{
        string variantName;
        DataType data;
    }VariantTable;
    
    typedef VariantTable ParamTable;
    
    typedef unordered_map<string,VariantTable*> VariantTables;
    typedef vector<ParamTable*> ParamTables;
    
    typedef VariantTables::iterator VariantTableIterator;
    typedef ParamTables::iterator ParamTableIterator;

}
#endif

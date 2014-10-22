//
//  TestSignal.h
//  TestMacro
//
//  Created by yafacex on 14-6-27.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestMacro_TestSignal_h
#define TestMacro_TestSignal_h

#include "boost/signals2/signal.hpp"
#include <string>
using namespace std;
namespace bs2 = boost::signals2;

void haha(){
    
}
class kao{
public:
    int val;
    bool caoa(){
        return false;
    };
};
class button{
public:
    button(){};
    ~button(){};
    
    typedef bs2::signal<void(int times,string msg)> signal_t;
    typedef bs2::signal<int()> sig_bool_t;
    typedef signal_t::slot_type slot_t;
    signal_t sig;
    sig_bool_t sigBool;
    void regist(const slot_t& slot){
        sig.connect(slot);
    }
    
    void print1(int times,string msg){
        for(int i=0;i<times;++i){
            printf("%s\n",msg.c_str());
        }
    };
    void print2(int times,string msg){
        for(int i=0;i<times;++i){
            printf("%d_%s\n",i,msg.c_str());
        }
    };
    int printBool(){
        return 11;
    }
};

class TestSignal {
public:
    TestSignal(){
        test();
//        vector<kao> a;
//        for_each(a.begin(),a.end(),mem_fun_ref(&kao::caoa));
//        for_each(a.begin(),a.end(),bind(&kao::caoa,this));
    };
    ~TestSignal(){};
    
    void caoa(){};
    void test(){
        button* btn = new button();
        button* btn1 = new button();
        int i=0;
        btn->regist(bind(&button::print1,btn1,_1,_2));
        btn->sig.connect(++i,bind(&button::print1,btn1,_1,_2));
        btn->sig.connect(--i,bind(&button::print2,btn1,_1,_2));
        btn->sigBool.connect(bind(&button::printBool,btn));
        string s = "nimabi";
        printf("\n=============\n");
        btn->sig(3,s);
//        delete btn1;
//        delete btn;
//        delete btn1;
//        delete btn1;
        printf("\n=============\n");
        btn->sig(3,s);
        printf("\n=============\n");
        btn->sig(3,s);
        
        vector<int> v;
//        for_each(v.begin(),v.end(),bind2nd(TestSignal::one,this));
        int b = *(btn->sigBool());
    };
    
    void one(int a){
        
    }
};

#endif

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
void gaga(int a,int b,int c){
    
}
void yaya(int a){
    printf("yaya %d",a);
}

template<typename T>
struct maximum
{
    typedef T result_type;
    
    template<typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const
    {
        if(first == last ) return T();
        T max_value = *first++;
        while (first != last) {
            if (max_value < *first)
                max_value = *first;
            ++first;
        }
        
        return max_value;
    }
};



class button{
public:
    button(){};
    ~button(){};
    
    typedef bs2::signal<void(int times,string msg)> signal_t;
    typedef bs2::signal<void(int,int,int)> signal_t_3int;
    typedef bs2::signal<int()> sig_bool_t;
    typedef signal_t::slot_type slot_t;
    signal_t sig;
    sig_bool_t sigBool;
    signal_t_3int sigInt3;
    signals2::signal<int (),  maximum<int> > sigMax;
    signals2::signal<int () > sigVec;
    
    void regist(const slot_t& slot){
        sig.connect(slot);
    }
    
    void print1(int times,string msg){
        printf("print1 %d %s\n",times,msg.c_str());
    };
    void print2(int times,string msg){
        printf("print2 %d %s\n",times,msg.c_str());
    };
    int printBool(){
        printf("testBool\n");
        return 111111;
    }
};

class TestSignal {
public:
    TestSignal(){
        test();
    };
    ~TestSignal(){};
    
    void test(){
//        testMem_Fun_Ref();
//        testSlot();
//        testReturnValue();
//        testCrossRegist();
//        testPrior();
//        testSTL_Capatiable();
//         testAutoDisconnect();
        testCombine();
    };
    
    void testSlot(){
        button* btn = new button();
        btn->regist(bind(&button::print1,btn,_1,_2));
        btn->sig(1,"aaa");
    }
    
    
    void testReturnValue(){
        button* btn = new button();
        btn->sigBool.connect(bind(&button::printBool,btn));
        int b = *(btn->sigBool());
        printf("b is %d\n",b);
    }
    
    void testCrossRegist(){
        button* btn = new button();
        button* btn1 = new button();
        btn->sig.connect(bind(&button::print1,btn1,_1,_2));
        btn->sig.connect(bind(&button::print2,btn1,_1,_2));
        btn->sig(3,"haha");
    }
    
    void testPrior(){
        button* btn = new button();
        btn->sig.connect(0,bind(&button::print1,btn,_1,_2));
        btn->sig.connect(1,bind(&button::print2,btn,_1,_2));
        btn->sig(3,"haha");
        printf("+++++++++\n");
        btn->sig.disconnect_all_slots();
        btn->sig.connect(1,bind(&button::print1,btn,_1,_2));
        btn->sig.connect(0,bind(&button::print2,btn,_1,_2));
        btn->sig(4,"haha");
    }
    
    void testAutoDisconnect(){
        shared_ptr<button> btn;
        btn->sig.connect(bind(&button::print1,btn,_1,_2));
        btn->sig(2,"aa");
    }
    bool ifEq2(int a){
        return a == 2;
    }
    void printInt(int a){
        printf("printInt %d\n",a);
    }
    void testSTL_Capatiable(){
        vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(2);
        v.push_back(4);
        for_each(v.begin(),v.end(),bind(&TestSignal::printInt,this,_1));
        v.erase(std::remove_if(v.begin(),v.end(),bind(&TestSignal::ifEq2,this,_1)),v.end());
        printf("after remove\n");
        for_each(v.begin(),v.end(),bind(&TestSignal::printInt,this,_1));
    }
   
    int ret1(){return 1;};
    int ret8(){return 8;};
    int ret4(){return 4;};
    void testCombine(){
        button* btn = new button();
        btn->sigMax.connect(bind(&TestSignal::ret1,this));
        btn->sigMax.connect(bind(&TestSignal::ret8,this));
        btn->sigMax.connect(bind(&TestSignal::ret4,this));
        btn->sigMax.connect(bind(&TestSignal::ret4,this));
        float res = btn->sigMax();
        printf("max is %f\n",res);
        btn->sigVec.connect(bind(&TestSignal::ret1,this));
        btn->sigVec.connect(bind(&TestSignal::ret8,this));
        btn->sigVec.connect(bind(&TestSignal::ret4,this));
        btn->sigVec.connect(bind(&TestSignal::ret4,this));
        float res1 = *btn->sigVec();
        printf("last is %f\n",res1);
    }
    
    void forTestMem_Fun_Ref(int a){
        printf("hoooo:%d\n",a);
    }
    void testMem_Fun_Ref(){
        vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
//        for_each(v.begin(),v.end(),mem_fun_ref(&TestSignal::forTestMem_Fun_Ref,this));
    }
    
    void forTestSTL_Bind_For(int a){
        printf("number is %d\n",a);
    }
    void testSTL_Bind(){
        vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
//        for_each(v.begin(),v.end(),bind2nd(&TestSignal::forTestSTL_Bind_For));
    }
};

#endif

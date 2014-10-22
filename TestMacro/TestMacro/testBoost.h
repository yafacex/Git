//
//  testBoost.h
//  TestMacro
//
//  Created by yafacex on 14-6-24.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestMacro_testBoost_h
#define TestMacro_testBoost_h
#include "boost/progress.hpp"
#include "boost/signals2/signal.hpp"
#include <iostream>
using namespace boost;

int haha(int a){
    std::cout<<"haha"<<std::endl;
    return 2 * a;
};
int gaga(int a){
    std::cout<<"gaga"<<std::endl;
    return 3 * a;
};


struct HelloWorld {
    void operator()() const {
        std::cout << "Hello, World" << std::endl;
    }
};

class Observer{
public:
    Observer(){};
    ~Observer(){};
    void doIt(){
        
    };
};
class Subject{
public:
    Subject(){};
    ~Subject(){};
};

class testBoost {
public:
    testBoost(){
        test();
    };
    
   
    
    ~testBoost(){};
    
    void test(){
        testSignal();
    };
   
    void testSignal(){
        typedef boost::signals2::signal<int (int)> signal_t;
        signal_t sig;
//        signal_t::extended_slot_type sigE(&haha,_1,"cao");
        sig.connect(1,haha);
        sig.connect(0,gaga);
        sig.connect(gaga);
//        int a = *sig(2);
//        sig.connect_extended(&sigE);
        sig(2);
    };
    
    
    
    
    void testProgress(){
        long n = INT64_MAX>>32;
        boost::progress_display pd(n);
        for (long i = 0; i < n; ++i) {
            ++pd;
        }
    };
};

#endif

//
//  TestTest.h
//  TestMacro
//
//  Created by yafacex on 14-6-30.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestMacro_TestTest_h
#define TestMacro_TestTest_h
#include "boost/static_assert.hpp"
class TestTest{
public:
    TestTest(){
        test();
    };
    ~TestTest(){};
    
    void test(){
        BOOST_ASSERT(false && "wocao");
    };
};


#endif

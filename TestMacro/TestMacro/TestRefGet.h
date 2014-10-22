//
//  TestRefGet.h
//  TestMacro
//
//  Created by yafacex on 14-7-10.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestMacro_TestRefGet_h
#define TestMacro_TestRefGet_h

class clsB{
public:
    int b;
    ~clsB(){
        printf("haB\n");
    };
};

class clsA{
public:
    clsB cb;
    clsB& getB(){
        return cb;
    }
};

class TestRefGet {
public:
    TestRefGet(){
        printf("ha1\n");
        clsA a;
        clsB b = a.getB();
        printf("ha2\n");
    };
    ~TestRefGet(){};
    
    
};

#endif

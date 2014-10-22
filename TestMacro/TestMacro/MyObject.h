//
//  MyObject.h
//  TestMacro
//
//  Created by yafacex on 14-2-27.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestMacro__MyObject__
#define __TestMacro__MyObject__

#include <iostream>
#include "autoserial/autoserial.h"
#include "classfactory.h"

class MyObject : public autoserial::ISerializable
{
    AS_CLASSDEF(MyObject)                 // Class name
    AS_MEMBERS
    AS_ITEM(int, a)                    // Declares "int a;"
    AS_ITEM(double, b)                 // Declares "double b;"
    AS_ITEM(std::vector<double>, v)    // Declares "std::vector v;"
    AS_CLASSEND;
};
class Interface{
public:
    Interface(){};
    ~Interface(){};
    virtual void func()=0;
};
class Cls1:public Interface{
public:
    Cls1(){};
    ~Cls1(){};
    virtual void func(){
        printf("cls1");
    }
};
class Cls2:public Cls1{
public:
    Cls2(){};
    ~Cls2(){};
    virtual void func(){
        printf("cls2");
    }
};
static void testMyObject(){
    Cls1 cls1;
    Cls2 cls2;
    printf("ccccccc");
    cls1.func();
    printf("ccccccc");
    cls2.func();
}


#endif /* defined(__TestMacro__MyObject__) */

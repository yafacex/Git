//
//  TestAllocator.h
//  TestMacro
//
//  Created by yafacex on 14-3-28.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestMacro__TestAllocator__
#define __TestMacro__TestAllocator__

#include <iostream>
class TestAllocator{
public:
    TestAllocator();
    ~TestAllocator(){};
    
    static void* operator new(size_t size){
        printf("override new");
        return (TestAllocator*)malloc(sizeof(TestAllocator));
//        return ::operator new(size);
    };
    
    int pa;
};
#endif /* defined(__TestMacro__TestAllocator__) */

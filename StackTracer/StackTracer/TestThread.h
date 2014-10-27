//
//  TestThread.h
//  StackTracer
//
//  Created by yafacex on 14-10-27.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __StackTracer__TestThread__
#define __StackTracer__TestThread__

class TestThread{
public:
    TestThread();
    void testFork();
    void testVFork();
    void testClone();
};
#endif /* defined(__StackTracer__TestThread__) */

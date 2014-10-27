//
//  TestThread.cpp
//  StackTracer
//
//  Created by yafacex on 14-10-27.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "TestThread.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
static int k = 0;
TestThread::TestThread(){
    testFork();
}
void TestThread::testFork(){
    pid_t pid = fork();
    
    switch (pid) {
        case -1:
            printf("fork failed!\n");
            break;
        case 0:{
            k = 250;
            sleep(3);
            printf("fork in Child,pid[%d],ppid[%d],k[%d]\n",getpid(),getppid(),k);
            sleep(3);
        }
            break;
        default:{
            k = 38000000;
            int status =0;
            pid_t waitid = wait(&status);
            printf("fork in Parent,pid[%d],ppid[%d],k[%d],status[%d],waitid[%d]\n",getpid(),getppid(),k,status,waitid);
        }
            break;
    }
}
void TestThread::testVFork(){
    pid_t pid = vfork();
    switch (pid) {
        case -1:
            printf("vfork failed!\n");
            break;
        case 0:{
            k = 250;
            sleep(2);
            printf("vfork in Child,pid[%d],ppid[%d],k[%d]\n",getpid(),getppid(),k);
            sleep(2);
            exit(0);
        }
            break;
        default:{
            int status =0;
            k = 380;
            pid_t waitid = wait(&status);
            printf("vfork in Parent,pid[%d],ppid[%d],k[%d],status[%d],waitid[%d]\n",getpid(),getppid(),k,status,waitid);
        }
            break;
    }
}
void TestThread::testClone(){
    
}
//
//  TestPTrace.cpp
//  StackTracer
//
//  Created by yafacex on 14-10-27.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "TestPTrace.h"
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ptrace.h>
//#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
TestPTrace::TestPTrace(){
    registerGet();
}

void TestPTrace::registerGet(){
    pid_t pid = fork();
    if (pid < 0) {
        printf("fork failed!\n");
    }else if(pid == 0){
        printf("fork in Child,execute <ls>\n");
        execl("/bin/ls", "ls", NULL);
    }else{
        printf("fork in Parent\n");
        wait(NULL);
        long orig_eax;
        orig_eax = ptrace(PTRACE_PEEKUSER,
                          child, 4 * ORIG_EAX,
                          NULL);
        printf("The child made a "
               "system call %ld ", orig_eax);
        ptrace(PTRACE_CONT, child, NULL, NULL);
    }
}
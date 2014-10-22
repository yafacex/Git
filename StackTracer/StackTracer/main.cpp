//
//  main.cpp
//  StackTracer
//
//  Created by yafacex on 14-10-22.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <vector>

void onSigSend(int sig, struct __siginfo *info,
		       void *uc){
    printf("hahaha\n");
}
void doNullPtr(){
    int * a = NULL;
    *a = 0;
}
void doDivZero(){
    int a = 0;
    a = 1 / a;
}
int main(int argc, const char * argv[])
{
    stack_t curStk,lastStk;
    struct sigaction curSigAct,lastSigAct;
    
    curStk.ss_sp = malloc(SIGSTKSZ);
    curStk.ss_size = SIGSTKSZ;
    sigaltstack(&curStk, &lastStk);
    
    curSigAct.sa_sigaction = onSigSend;
    curSigAct.sa_flags = SA_ONSTACK | SA_SIGINFO;
    sigaction(SIGSEGV, &curSigAct, &lastSigAct);
    
    doNullPtr();
    return 0;
}




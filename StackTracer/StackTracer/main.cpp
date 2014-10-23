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

//#define _STRUCT_UCONTEXT	struct ucontext
//#endif /* __DARWIN_UNIX03 */
//_STRUCT_UCONTEXT
//{
//	int                     uc_onstack;
//	__darwin_sigset_t       uc_sigmask;     /* signal mask used by this context */
//	_STRUCT_SIGALTSTACK     uc_stack;       /* stack used by this context */
//	_STRUCT_UCONTEXT        *uc_link;       /* pointer to resuming context */
//	__darwin_size_t	        uc_mcsize;      /* size of the machine context passed in */
//	_STRUCT_MCONTEXT        *uc_mcontext;   /* pointer to machine specific context */
//#ifdef _XOPEN_SOURCE
//	_STRUCT_MCONTEXT        __mcontext_data;
//#endif /* _XOPEN_SOURCE */
//};

//#define	_STRUCT_MCONTEXT64	struct __darwin_mcontext64
//_STRUCT_MCONTEXT64
//{
//	_STRUCT_X86_EXCEPTION_STATE64	__es;
//	_STRUCT_X86_THREAD_STATE64	__ss;
//	_STRUCT_X86_FLOAT_STATE64	__fs;
//};

//#if __DARWIN_UNIX03
//#define	_STRUCT_X86_THREAD_STATE64	struct __darwin_x86_thread_state64
//_STRUCT_X86_THREAD_STATE64
//{
//	__uint64_t	__rax;
//	__uint64_t	__rbx;
//	__uint64_t	__rcx;
//	__uint64_t	__rdx;
//	__uint64_t	__rdi;
//	__uint64_t	__rsi;
//	__uint64_t	__rbp;
//	__uint64_t	__rsp;
//	__uint64_t	__r8;
//	__uint64_t	__r9;
//	__uint64_t	__r10;
//	__uint64_t	__r11;
//	__uint64_t	__r12;
//	__uint64_t	__r13;
//	__uint64_t	__r14;
//	__uint64_t	__r15;
//	__uint64_t	__rip;
//	__uint64_t	__rflags;
//	__uint64_t	__cs;
//	__uint64_t	__fs;
//	__uint64_t	__gs;
//};

//#if __DARWIN_UNIX03
//#define	_STRUCT_X86_FLOAT_STATE64	struct __darwin_x86_float_state64
//_STRUCT_X86_FLOAT_STATE64
//{
//	int 			__fpu_reserved[2];
//	_STRUCT_FP_CONTROL	__fpu_fcw;		/* x87 FPU control word */
//	_STRUCT_FP_STATUS	__fpu_fsw;		/* x87 FPU status word */
//	__uint8_t		__fpu_ftw;		/* x87 FPU tag word */
//	__uint8_t		__fpu_rsrv1;		/* reserved */
//	__uint16_t		__fpu_fop;		/* x87 FPU Opcode */
//    
//	/* x87 FPU Instruction Pointer */
//	__uint32_t		__fpu_ip;		/* offset */
//	__uint16_t		__fpu_cs;		/* Selector */
//    
//	__uint16_t		__fpu_rsrv2;		/* reserved */
//    
//	/* x87 FPU Instruction Operand(Data) Pointer */
//	__uint32_t		__fpu_dp;		/* offset */
//	__uint16_t		__fpu_ds;		/* Selector */
//    
//	__uint16_t		__fpu_rsrv3;		/* reserved */
//	__uint32_t		__fpu_mxcsr;		/* MXCSR Register state */
//	__uint32_t		__fpu_mxcsrmask;	/* MXCSR mask */
//	_STRUCT_MMST_REG	__fpu_stmm0;		/* ST0/MM0   */
//	_STRUCT_MMST_REG	__fpu_stmm1;		/* ST1/MM1  */
//	_STRUCT_MMST_REG	__fpu_stmm2;		/* ST2/MM2  */
//	_STRUCT_MMST_REG	__fpu_stmm3;		/* ST3/MM3  */
//	_STRUCT_MMST_REG	__fpu_stmm4;		/* ST4/MM4  */
//	_STRUCT_MMST_REG	__fpu_stmm5;		/* ST5/MM5  */
//	_STRUCT_MMST_REG	__fpu_stmm6;		/* ST6/MM6  */
//	_STRUCT_MMST_REG	__fpu_stmm7;		/* ST7/MM7  */
//	_STRUCT_XMM_REG		__fpu_xmm0;		/* XMM 0  */
//	_STRUCT_XMM_REG		__fpu_xmm1;		/* XMM 1  */
//	_STRUCT_XMM_REG		__fpu_xmm2;		/* XMM 2  */
//	_STRUCT_XMM_REG		__fpu_xmm3;		/* XMM 3  */
//	_STRUCT_XMM_REG		__fpu_xmm4;		/* XMM 4  */
//	_STRUCT_XMM_REG		__fpu_xmm5;		/* XMM 5  */
//	_STRUCT_XMM_REG		__fpu_xmm6;		/* XMM 6  */
//	_STRUCT_XMM_REG		__fpu_xmm7;		/* XMM 7  */
//	_STRUCT_XMM_REG		__fpu_xmm8;		/* XMM 8  */
//	_STRUCT_XMM_REG		__fpu_xmm9;		/* XMM 9  */
//	_STRUCT_XMM_REG		__fpu_xmm10;		/* XMM 10  */
//	_STRUCT_XMM_REG		__fpu_xmm11;		/* XMM 11 */
//	_STRUCT_XMM_REG		__fpu_xmm12;		/* XMM 12  */
//	_STRUCT_XMM_REG		__fpu_xmm13;		/* XMM 13  */
//	_STRUCT_XMM_REG		__fpu_xmm14;		/* XMM 14  */
//	_STRUCT_XMM_REG		__fpu_xmm15;		/* XMM 15  */
//	char			__fpu_rsrv4[6*16];	/* reserved */
//	int 			__fpu_reserved1;
//};
void onSigSend(int sig, struct __siginfo *info,
		       void *uc){
    ucontext_t* context = (ucontext_t*)uc;
    uint64_t rax = context->uc_mcontext->__ss.__rax;
    uint64_t rip = context->uc_mcontext->__ss.__rip;
    printf("rax : %llx\n",rax);
    printf("rip : %llx\n",rip);
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




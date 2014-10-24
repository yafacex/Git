//
//  TestEfficience.h
//  TestMacro
//
//  Created by yafacex on 14-6-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestMacro_TestEfficience_h
#define TestMacro_TestEfficience_h
#include <vector>
#include <sys/time.h>
#include <ranlib.h>
//#include "includes/OIS.h"
//#include "LIBA.h"
using namespace std;

class TestEfficience{
public:
    TestEfficience(){
//        int cao =OIS::InputManager::getVersionNumber();
//        LIBA la;
//        int n=la.getNumber();
//        printf("%d",n);
//        int num = OIS::InputManager::getVersionNumber();
        test();
    };
    ~TestEfficience(){};
    
    int N_;
    std::vector<int> cao;
    long clk ;
    int i=0;

    class itrr{
    public:
        inline itrr(){};
        inline int* getBase() const{return p;};
        inline bool operator!=(itrr& rv){
            return !(getBase()==rv.getBase());
        }
        int *p ;
    };
    class itrrItr{
    public:
        inline itrrItr(itrr* i){
            cur = i;
        };
        itrr* cur;
        inline itrrItr& operator++(){
            ++cur;
            return *this;
        }
        inline bool operator!=(const itrrItr& rv){
            return !(this->cur->getBase()==rv.cur->getBase());
        }
        inline int& operator*() const{
            return *(cur->getBase());
        }
    };
    itrr *a ;
    itrr* pEnd;

    int *b;
    
    int outer ;
    int zOuter = 5;
    
    long sert =0;
    void noTemplate(){
        printf("noTemplate\n");
        clk = gettime();
        i=0;
        sert = 0;
        itrrItr itrEnd(pEnd);
        itrr* pBegin = &a[0];
        for (int z = 0; z<zOuter; ++z) {
            for (int k=0; k<outer; ++k) {
                itrrItr itr(pBegin);
                while (itr!=itrEnd) {
                    //            int *h = p->p;
                    //            printf("haha");
                    //            printf("haha %x %x %x\n",p,h,*h);
                    ++itr;
                    ++sert;
                    (*itr) += 5;
                    //            printf("after:%x\n",p);
                }
            }
        }
        
        
        printf("A:time:%ld-''''cnt:%ld\n",(gettime()-clk),sert);
    }
    void noTemplate2(){
        printf("Origin\n");
        clk = gettime();
        sert = 0;
        for (int z = 0; z<zOuter; ++z) {
            for (int k=0; k<outer; ++k) {
                for(int i = 0;i<N_;++i){
                    ++sert;
                    b[i] = 5;
                }
            }
        }
        
        printf("C:time:%ld-''''cnt:%ld\n",(gettime()-clk),sert);
    }
    void withTemplate(){
        printf("withTemplate\n");
        clk = gettime();
        sert =0;
        for (int z = 0; z<zOuter; ++z) {
            for (int k = 0; k<outer; ++k) {
                for(vector<int>::iterator itr = cao.begin(); itr != cao.end(); ++itr){
                    (*itr) = 5;
                    ++sert;
                }
            }
        }
        printf("B:time:%ld-''''%ld\n",(gettime()-clk),sert);
    }
    void test(){
        outer = getRand(99999, 999999);
        zOuter = getRand(22, 55);
        N_ = getRand(33, 55);
        
        a = (itrr*)malloc(sizeof(itrr)*N_);
        b = (int*)malloc(sizeof(int)*N_);
        
        for (i=0;i<N_; ++i) {
            int* pp = new int();
            *pp = i;
            a[i].p = pp;
        }
        pEnd = &a[N_-1];
        
        for (int i =0; i<N_; ++i) {
            cao.push_back(i);
        }
        
    
//        noTemplate();
        withTemplate();
        noTemplate2();



        
        
    };
    
    inline long gettime(){
        return clock();
        struct timeval t;
        gettimeofday(&t, NULL);
        return t.tv_sec* 1000000 + t.tv_usec;
    }
    
    int getRand(int min,int max){
        int rand = (int)random();
        return min + (max - min) * rand / INT32_MAX;
    }
};
#endif

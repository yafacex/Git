//
//  TestFindIf.h
//  TestMacro
//
//  Created by yafacex on 14-3-5.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestMacro__TestFindIf__
#define __TestMacro__TestFindIf__

#include <iostream>

template<class _II, class _Pr, class T_DATA> inline
_II
TDfind_if(
          _II _F, // First iterator
          _II _L, // Last iterator
          _Pr _P, // Predicate: a static function that returns bool having two
          T_DATA dwData)
{
    for (; _F != _L; ++_F)
    {
        if (_P(*_F, dwData))
        {
            break;
        }
    }
    
    return (_F);
}


template<class _II, class _Fn, class T_DATA> inline
void
TDfor_each(
           _II _F,
           _II _L,
           _Fn _Op,
           T_DATA dData)
{
    for (; _F != _L; ++_F)
    {
        _Op(*_F, dData);
    }
}

class show{
public:
    show(int* addr,int a){};
    ~show(){};
    void operator()(int *addr,int a){
        std::cout<<"addr:"<<addr<<","<<a<<std::endl;
    }
};

using namespace std;
class TestFindIf{
public:
    TestFindIf(){};
    ~TestFindIf(){};
    void show(int* addr,int a){
        
    }
    void TestFindIfMain(){
//        int theList[5];
//        ::TDfor_each(&theList[0], &theList[4], show(0,1), 99);
    }
};
//class TestMacro{
//    
//};
#endif /* defined(__TestMacro__TestFindIf__) */

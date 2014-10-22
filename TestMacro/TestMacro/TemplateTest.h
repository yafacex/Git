//
//  TemplateTest.h
//  TestMacro
//
//  Created by yafacex on 14-2-28.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestMacro_TemplateTest_h
#define TestMacro_TemplateTest_h

#include "ObserverPatternMini.h"

#define STATE_CONSTRUCTOR(cls)\
public: cls(){};~cls(){};

#define PRINT_CLS_PREFIX(cls)\
printf(#cls);\

using namespace std;
using namespace ObserverNS;
void testForeach();

struct msg{
    int a;
    float b;
    string c;
};
struct msg2{
    string a;
    string b;
};

class model:public SubjectList<struct msg,struct msg2>{
public:
    model(){};
    virtual ~model(){};
    
    void doSomething(){
        struct msg2 caca = {"jjjj","hhhhh"};
        notify(caca);
       
        struct msg gaga = {4,5,"gaga"};
        notify(gaga);
    };
};

class ctrler:public IObserverList<struct msg,struct msg2>{
public:
    ctrler(){};
    ~ctrler(){};
    void init(){
        mo.ObserverNS::Subject<msg>::attach(*this);
        mo.ObserverNS::Subject<msg2>::attach(*this);
        
        
        
        mo.doSomething();
//        struct msg m = {1,2.0,"aaa"};
//        
//        Subject<struct msg> aa;
//        aa.attach(*this);
//        aa.notify(m);
    }
    
    virtual void onMsgSend(struct msg& mmsg){
        printf("yeah %d , %f , %s", mmsg.a,mmsg.b,mmsg.c.c_str());
    }
    virtual void onMsgSend(struct msg2& mmsg){
        printf("yeah %s, %s", mmsg.a.c_str(),mmsg.b.c_str());
    }
protected:
    model mo;
};

template<typename T>
class CC2{
public:
    virtual ~CC2(){};
    void addVal(T v){mStore.push_back(v);};
    vector<T> getAll(){return mStore;};
    virtual void orf(){};
protected:
    vector<T> mStore;
};

template<typename... Ts>
class CC1:public CC2<Ts>...{
public:
    virtual ~CC1(){};
    template<typename T>
    void addV(T v){
        CC2<T>::addVal(v);
    };
    template<typename T>
    vector<T> getV(T one){
       return  CC2<T>::getAll();
    }
    virtual void orf(){};
};
class KKK{};
class CCCC{
public:
    CCCC(){};
    template<typename T,typename T2>
    void func(int a,const char* s){ T b = 2;a = a * 2;
        printf("111 %s",s);};
    
    template<typename T,typename T2>
    void func(int a,int i,T2* t2){
        T* b = new T();
        t2 = NULL;
        a = 2 * a;
        printf("222 %d",i);};
};
void templateTestMain(){
//    CC1<float,string,int,double,const char*> cc1;
//    string c = "aaaa";
//    cc1.addV(1);
//    cc1.addV(c);
//    cc1.addV("aaaas");
//    cc1.addV(4444.0);
//    cc1.orf();
//
//    vector<const char *> all = cc1.getV("");
//    cout<<"Template!!!!!!!!!!!!!!"<<endl;
//    testForeach();
//    ctrler a;
//    a.init();
    CCCC c;
    KKK* k = new KKK();
    c.func<KKK>(1, 1,k);
    cout<<endl<<"TemplateEnd!!!!!!!!!!!!!!"<<endl;
}

template <class _InputIterator, class _Function>
_Function
for_each2(_InputIterator __first, _InputIterator __last, _Function __f)
{
    for (; __first != __last; ++__first)
        __f(*__first);
//    return _VSTD::move(__f);
}
template <typename T>
T funcc(T a) {
    cout<<"***********"<<endl;
}

class callCls{
public:
    callCls(){};
    ~callCls(){};
    void operator()(int itr){
        cout<<"Itr is:"<<itr<<endl;
    }
};
void testForeach(){
    vector<int> vecInt,vecInt1;
    vecInt.push_back(1);
    vecInt.push_back(3);
    vecInt.push_back(5);
    
    int a[5]={1,2,3,4,5};
    funcc(vecInt1);
 
//    template<typename T>
//    inline _LIBCPP_INLINE_VISIBILITY
//    T haha(){
//        cout<<"SSSSSSS"<<endl;
//    }
    for_each2(vecInt.begin(),vecInt.end(),callCls());
    for_each2(a,a+4,callCls());
}

class testFuncTemplate{
    STATE_CONSTRUCTOR(testFuncTemplate);
    
    void run(){
        PRINT_CLS_PREFIX(testFuncTemplate)
        
    };
    class CLS1{
    public:
        CLS1(){};
        ~CLS1(){};
    };
    CLS1 getNewCLS1(int n){
        printf("%d--",n);
        return *(new CLS1());
    }

    template <typename T>
    CLS1 func(CLS1 (*func)(T)) {
        return func(1);
    }
};

#endif

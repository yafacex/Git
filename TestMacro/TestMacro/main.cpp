//
//  main.cpp
//  TestMacro
//
//  Created by yafacex on 14-1-21.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
//#include <tuple>
#include <time.h>
#include "MyObject.h"
#include "as_file.h"
#include "TemplateTest.h"
#include "TestAllocator.h"
#include "TestEfficience.h"
#include "testBoost.h"
#include "TestSignal.h"
#include "TestTest.h"
#include "TestRegex.h"
#include "TestRefGet.h"

using namespace std;

//typedef std::tuple<class none,int,string> tuple3;

class Basic
{
public:
    void print(){
        printf("basic\n");
    };
};
class Derived1 : public Basic
{
public:
    Derived1() {}
    
    void print(){
        printf("de 1111111\n");
    };
    
};
class Derived2 : public Basic
{
public :
    Derived2() {}
    
    void print(){
        printf("de 2222222\n");
    };
};
template <class T>
class  Printer{
public:
    Printer():a(10){};
    ~Printer(){};
    void tprint(){
        t.print();
        printf("%d --->hah",a);
    };
    
    Printer<T> & operator=(Printer<T> const &a){
        this->t = a.t;
        return *this;
    };
    
    
    T t;
    
    int a;
};

template <class T>
class T_basic {
public:
    void print(){printf("t_basic\n");};
    T t;
    T_basic &operator=(const T_basic &a){
        return *this;
    };
};

template <class T>
class T_1:public T_basic<T>{
public:
    void print(){printf("t_1\n");};
};

template <class T>
class T_2:public T_basic<T>{
public:
    void print(){printf("t_2\n");};
};

class none1{
public:
    none1():num(10),mRef(1){};
    ~none1(){};
    
    int num;
    void retain(){++mRef;};
    void release(){--mRef;if(mRef==0)delete this;};
protected:
    int mRef;
};

void testTemplateInherit(){
    Printer<Basic> *basic=new Printer<Basic>();
    Printer<Basic> basic2;
    Printer<Derived1> *derived1=new Printer<Derived1>;
    Printer<Derived2> *derived2=new Printer<Derived2>;
    
    derived1->tprint();
    derived2->tprint();
    
//    basic = dynamic_cast<Printer<Basic>* >(derived1);

};

void testClassWithTemplateInherit(){
    T_basic<none1> *tb = new T_basic<none1>();
    T_1<none1> *t1 = new T_1<none1>();
    T_2<none1> *t2 = new T_2<none1>();
    tb = t1;
    tb->print();
//    tb = static_cast<T_basic<none>* >(t1);
    t1->print();
    t2->print();
}

//std::tuple<class none,float,std::string> testTuple(){
//    none n;
//    float f=2.0;
//    string s = "sbzm";
//    std::tuple<class none,float,std::string> a=std::make_tuple(n,f,s);
//    
//    cout<<get<0>(a).num<<endl;
//    cout<<get<1>(a)<<endl;
//    cout<<get<2>(a)<<endl;
//
//    return a;
//}

#define MIN(x,y) (x<y?x:y)
#define _CONTAINER(__TYPE__) <__TYPE__>
#define _ITR(__TYPE__,__CON__) __CON__ _CONTAINER(__TYPE__)::iterator itr;

#define _SEE_MACRO(x) #x
#define SEE_MACRO(x) _SEE_MACRO(x)
#define SEE_MACRO2(x) SEE_MACRO(x)
#define SEE_MACRO3(x) SEE_MACRO(x)

void testMacroExpand(){
    vector <int> a;
    const char *str = SEE_MACRO(_ITR(int,vector));
    printf("%s",str);
}

//template <typename LT,typename LR>
//auto add(LT l,LR r)->decltype(l+r) {
//    return l + r;
//}
template <typename T>
T getSameTypeObject(T const& t) {
    return t;
}



int main(int argc, const char * argv[])
{
//    testTemplateInherit();
//    printf("\n\n\n");
//    testClassWithTemplateInherit();
//    printf("\n\n\n");
//    
//    none no;
//    float f;
//    string s;
//    std::tie(no,f,s) = testTuple();
//    printf("%d ,%f, %s\n",no.num,f,s.c_str());
//    
//    shared_ptr<none> sptr(new none());
//    cout<<"sptr_cnt1 "<<sptr.use_count()<<endl;
//    shared_ptr<none> sptr1 = sptr;
//    cout<<"sptr_cnt2 "<<sptr.use_count()<<endl;
//    sptr1->num = 250;
//    cout<<"sptr_cnt3 "<<sptr.use_count()<<endl;
//    sptr1 = nullptr;
//    cout<<"sptr_cnt4 "<<sptr.use_count()<<endl;
//    
//    int i,j;
//    clock_t t=clock();
//    for (i=0; i<10; ++i) {
//        none *nn = new none();
//        for (j=0; j<10000; ++j) {
//            nn->retain();
//            nn->release();
////            nn->release();
//        }
//    }
//    t=clock() -t;
//    printf("manual:%d\n",int(t));
//    shared_ptr<none> tmpN;
//    for (i=0; i<10; ++i) {
//        shared_ptr<none> nn(new none());
//        for (j=0; j<10000; ++j) {
//            tmpN = nn;
//            nn = tmpN;
////            nn = tmpN;
//        }
//    }
//    t=clock() -t;
//    printf("sharedPtr:%d\n",int(t));
    
//    testMacroExpand();
//    MyObject obj;                           // Create and initialize the serializable object
//    obj.a = 1;
//    obj.b = 1.2;
//    obj.v.push_back(3.2);
//    char* a1 = SEE_MACRO(AS_CLASSDEF(MyObject1));
//    printf("%s\n",a1);
//    char* a2 = SEE_MACRO(AS_MEMBERS);
//    printf("%s\n",a2);
//    char* a5 = SEE_MACRO(AS_CLASSEND);
//    printf("%s",a5);
//    
//    autoserial::BinaryFileWriter bfw("myFile.bin");     // Open a binary file for writing
//    bfw.write(&obj);
//    float a=add(1.3, 2);
//    none one,two;
//    one.num=250;
//    two = getSameTypeObject(one);
//    two.num=380;
//    
//    T_basic<string> t;

//    templateTestMain();
//    testMyObject();
//    TestAllocator* allo = new TestAllocator;
//    allo->pa = 222;
//    printf("pa %d",allo->pa);
//    int a = 320,b = -20;
//    int n = 20000000;
//    
//    int n1=0,n2=0;
//    clock_t clk1 = clock();
//    for (int i=0; i<n; ++i) {
//
//        if(a * b < 0) {
//            n1++;
//        }
//    }
//    clock_t clk2 = clock();
//    for (int i=0; i<n; ++i) {
//
//        if (a>>31 ^ b>>31) {
//            n2++;
//        }
//    }
//    clock_t clk3 = clock();
//    printf("[%d %d]-- [%d %d]",clk2 - clk1,n1,clk3 - clk2,n2);
    
    TestEfficience ef;
//    testBoost tb;
//    TestSignal sig;
//    find_if(a.begin(),a.end(),std::mem_fun(&kao::caoa));
//    find_if(a.begin(), a.end(), bool [](int v){
//        return true;
//    });
//    TestTest test;
    TestRegex regex;
    
//    TestRefGet refGet;
}

//class MyObject1:public autoserial::ISerializable{
//public:
//    typedef MyObject1 containerType;
//private:
//    class ClassdefAndIdentifyAreRedundant { };
//    class EnsureCorrectIdentifyArgumentMyObject1 { };
//    typedef MyObject1::EnsureCorrectIdentifyArgumentMyObject1 EnsureCorrectIdentifyArgument;
//public:
//    static const char *getTypeName() { return "MyObject1"; }
//    autoserial::Result write(autoserial::IOutputStream* s) const {
//        autoserial::Result r;
//        if(((r=__baseClasses::write(s,*this))!=autoserial::AS_OK))
//            return r;
//        return __members::write(s,*this);
//    }
//    autoserial::Result read(autoserial::IInputStream* s) {
//        autoserial::Result r;
//        if(((r=__baseClasses::read(s,*this))!=autoserial::AS_OK))
//            return r;
//        return __members::read(s,*this);
//    }
//    void compare(autoserial::Comparator *v, const MyObject1& item) const {
//        __baseClasses::equals(v,*this,item);
//        __members::equals(v,*this,item);
//    }
//    virtual const char *getTypeNameV() const {
//        return getTypeName();
//    }
//    virtual Size getSizeV() const {
//        return sizeof(MyObject1);
//    }
//    static Size getTypeIndex() {
//        static autoserial::internal::GenericRegistrarHolder<MyObject1 > gch;
//        return gch.getTypeIndex();
//    }
//    virtual Size getTypeIndexV() const {
//        return getTypeIndex();
//    };
//    virtual autoserial::Result writeV(autoserial::IOutputStream* s) const {
//        return this->write(s);
//    }
//    virtual autoserial::Result readV(autoserial::IInputStream* s) {
//        return this->read(s);
//    }
//    virtual void compareV(autoserial::Comparator *v, const autoserial::ISerializable *s) const {
//        if(strcmp(getTypeNameV(),s->getTypeNameV())) {
//            v->memberEqual(false); return;
//        }
//        this->compare(v,*(MyObject1*)s);
//    }
//    virtual const char *getBaseClassNameV() const {
//        return MyObject1::baseClassAccessPoint::getBaseClassName();
//    }
//    virtual Size getFactoryTypeIndexV() const {
//        static autoserial::internal::GenericConstructorHolder<MyObject1 > gch;
//        return gch.getIndex();
//    }
//private:
//    typedef autoserial::internal::MemberStackTop<containerType>
//    __baseClasses;
//public:
//    typedef __baseClasses baseClassAccessPoint;
//private:
//    typedef autoserial::internal::MemberStackTop<containerType>
//    __members;
//public: enum { checkForBaseClasses = sizeof(__baseClasses) };
//};




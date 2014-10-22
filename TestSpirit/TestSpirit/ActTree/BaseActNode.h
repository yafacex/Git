//
//  BaseActNode.h
//  DragonEmpire
//
//  Created by yafacex on 14-8-6.
//
//

#ifndef __DragonEmpire__BaseActNode__
#define __DragonEmpire__BaseActNode__
#include <vector>
using namespace std;
enum ACT_STATUS{
    AS_Running,
    AS_Success,
    AS_Failure
};

class BaseActNode{
public:
    virtual ~BaseActNode(){};
    virtual ACT_STATUS execute() = 0;
    virtual void reset() = 0;
};


class CompositeActNode:public BaseActNode{
public:
    CompositeActNode(){};
    virtual ~CompositeActNode(){
        for (vector<BaseActNode*>::iterator itr = mChildren.begin();
             itr != mChildren.end(); ++itr) {
            delete *itr;
        }
        mChildren.clear();
    };
    
    virtual ACT_STATUS execute(){return AS_Success;};
    
    virtual void addChild(BaseActNode* child){
        mChildren.push_back(child);
    };
    
    virtual void reset() {
        for (vector<BaseActNode*>::iterator itr = mChildren.begin();
             itr != mChildren.end(); ++itr) {
            (*itr)->reset();
        }
    };
protected:
    vector<BaseActNode*> mChildren;
};

class SuccessAfterTimes:public BaseActNode{
public:
    SuccessAfterTimes(int times){
        mTimes = times;
    };
    virtual ~SuccessAfterTimes(){};
    
    virtual ACT_STATUS execute(){
        ++mCnter;
        if (mCnter > mTimes) {
            return AS_Success;
        }else{
            return AS_Running;
        }
    };
    virtual void reset() {mCnter = 0;};
protected:
    int mCnter;
    int mTimes;
};

class FailureAfterTimes:public BaseActNode{
public:
    FailureAfterTimes(int times){
        mTimes = times;
    };
    virtual ~FailureAfterTimes(){};
    virtual ACT_STATUS execute(){
        ++mCnter;
        if (mCnter > mTimes) {
            return AS_Failure;
        }else{
            return AS_Running;
        }
    };
    virtual void reset() {mCnter = 0;};
protected:
    int mCnter;
    int mTimes;
};

class SuccessAfterSec:public BaseActNode{
public:
    SuccessAfterSec(float sec){
        mFrmCnter = 0;
        mDelayFrm = sec * 30;
    };
    virtual ~SuccessAfterSec(){};
    
    virtual ACT_STATUS execute(){
        ++mFrmCnter;
        if (mFrmCnter > mDelayFrm) {
            return AS_Success;
        }else{
            return AS_Running;
        }
    };
    virtual void reset() {mFrmCnter = 0;};
protected:
    int mFrmCnter;
    int mDelayFrm;
};

class FailureAfterSec:public BaseActNode{
public:
    FailureAfterSec(float sec){
        mFrmCnter = 0;
        mDelayFrm = sec * 30;
    };
    virtual ~FailureAfterSec(){};
    
    virtual ACT_STATUS execute(){
        ++mFrmCnter;
        if (mFrmCnter > mDelayFrm) {
            return AS_Failure;
        }else{
            return AS_Running;
        }
    };
    virtual void reset() {mFrmCnter = 0;};
protected:
    int mFrmCnter;
    int mDelayFrm;
};
#endif /* defined(__DragonEmpire__BaseActNode__) */

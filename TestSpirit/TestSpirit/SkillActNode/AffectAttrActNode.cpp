//
//  AffectAttrActNode.cpp
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "AffectAttrActNode.h"

AffectAttrActNode::AffectAttrActNode(CCCharacterVector* result,Skill::DataRule* dataRule,CCGameCharacter* owner){
    mResult = result;
    mDataRule = dataRule;
    mOwner = owner;
}

ACT_STATUS AffectAttrActNode::execute(){
    switch(mDataRule->attr){
        case Skill::hp:{
            if (mDataRule->op == Skill::mul) {
                
            }else if(mDataRule->op == Skill::add){
                
            }
        }
            break;
        case Skill::attackspd:{
            if (mDataRule->op == Skill::mul) {
                
            }else if(mDataRule->op == Skill::add){
                
            }
        }
            break;
        case Skill::movespd:{
            if (mDataRule->op == Skill::mul) {
                
            }else if(mDataRule->op == Skill::add){
                
            }
        }
            break;
    }
    return AS_Success;
}
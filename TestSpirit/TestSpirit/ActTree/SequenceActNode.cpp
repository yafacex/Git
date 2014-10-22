//
//  SequenceActNode.cpp
//  BeTreeTest
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "SequenceActNode.h"

ACT_STATUS SequenceActNode::execute(){
    if (mChildren.size() > 0) {
        for (vector<BaseActNode*>::iterator itr = mChildren.begin();
             itr != mChildren.end(); ++itr) {
            switch ((*itr)->execute()) {
                case AS_Success:
                    //go on
                    break;
                case AS_Failure:
                    return AS_Failure;
                    break;
                case AS_Running:
                    return AS_Running;
                    break;
                default:
                    return AS_Failure;
                    break;
            }
        }
        return AS_Success;
    }else{
        return AS_Success;
    }
};


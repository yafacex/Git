//
//  SequenceActNode.h
//  BeTreeTest
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __BeTreeTest__SequenceActNode__
#define __BeTreeTest__SequenceActNode__
#include "BaseActNode.h"
class SequenceActNode:public CompositeActNode{
public:
    
    SequenceActNode(){};
    virtual ACT_STATUS execute();
};
#endif /* defined(__BeTreeTest__SequenceActNode__) */

//
//  TestWater.h
//  TestOpenglES
//
//  Created by yafacex on 14-7-14.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestOpenglES__TestWater__
#define __TestOpenglES__TestWater__

#include <OpenGL/gl.h>

#include <iostream>

class TestWater{
public:
    TestWater(){
        
    };
    void init(const char *filename);
    void draw_mesh(void);
    void update();
    void animate(void);
};
#endif /* defined(__TestOpenglES__TestWater__) */

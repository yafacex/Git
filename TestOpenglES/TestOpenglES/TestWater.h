//
//  TestWater.h
//  TestOpenglES
//
//  Created by yafacex on 14-7-14.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestOpenglES__TestWater__
#define __TestOpenglES__TestWater__

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include <iostream>

class TestWater{
public:
    void init(char *filename);
    void draw_mesh(void);
    void update();
};
#endif /* defined(__TestOpenglES__TestWater__) */

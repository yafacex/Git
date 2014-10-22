//
//  BWReader.h
//  TestOpenglES
//
//  Created by yafacex on 14-7-14.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestOpenglES__BWReader__
#define __TestOpenglES__BWReader__

#include <iostream>
class BWReader{
public:
    unsigned *
    read_texture(const char *name, int *width, int *height, int *components);
};
#endif /* defined(__TestOpenglES__BWReader__) */

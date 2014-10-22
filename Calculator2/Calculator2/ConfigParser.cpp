//
//  ConfigParser.cpp
//  Calculator2
//
//  Created by yafacex on 14-7-15.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "ConfigParser.h"

void ConfigParser::skipBlank(char* &str){
    int i = 0;
    while (*str == ' '|*str == '\t'|*str == EOF)
    {
        ++i;
        str = str + 1;
        if (i > 10)
        {
            break;
        }
    }
}
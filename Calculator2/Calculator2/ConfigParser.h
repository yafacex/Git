//
//  ConfigParser.h
//  Calculator2
//
//  Created by yafacex on 14-7-15.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __Calculator2__ConfigParser__
#define __Calculator2__ConfigParser__

#include <iostream>
class ConfigParser{
public:
    ConfigParser(){};
    ~ConfigParser(){};
    
    void skipBlank(char* &str);
};
#endif /* defined(__Calculator2__ConfigParser__) */

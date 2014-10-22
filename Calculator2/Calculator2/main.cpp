//
//  main.cpp
//  Calculator2
//
//  Created by yafacex on 14-7-15.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include <iostream>
#include "Formula.h"
int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    FormulaNS::Formula fml;
    float a1 = fml.calcByString("result = ((6-1));",true);
    printf("result = %f\n",a1);
    float b1 = fml.calcByOP();
    float a2 = fml.calcByString("result = (2 + 4)* 3 + 5;",true);
    float a3 = fml.calcByString("result = 2 + 4* (3 + 5);",true);
    float a5 = fml.calcByString("result = 2 + prev* 3 + 5;",true);
    float a6 = fml.calcByString("result = prev *(prev + 4)* 3 + 5/2;",true);
    float a7 = fml.calcByString("result = prev + 4* (3 + 5);",true);
    printf("%f,%f,%f",a1,a2,a3);
    return 0;
}


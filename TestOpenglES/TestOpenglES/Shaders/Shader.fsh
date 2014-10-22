//
//  Shader.fsh
//  TestOpenglES
//
//  Created by yafacex on 14-7-14.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}

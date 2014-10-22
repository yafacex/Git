//
//  CppRender.h
//  TestOpenglView
//
//  Created by yafacex on 14-2-24.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestOpenglView__CppRender__
#define __TestOpenglView__CppRender__


#include <iostream>


class CppRender{
public:
    CppRender(){};
    ~CppRender(){};
    static CppRender* getInstance(){
        if (!m_Instance) {
            m_Instance = new CppRender();
        }
        return m_Instance;
    };
    //render func
    void render();
    void update();
    void init();
    void initShader();
    GLuint initVertexShader();
    GLuint initFragmentShader();
private:
    float mRotate;
    
    static CppRender *m_Instance;
};
#endif /* defined(__TestOpenglView__CppRender__) */

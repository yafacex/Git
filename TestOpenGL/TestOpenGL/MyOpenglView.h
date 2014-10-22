//
//  MyOpenglView.h
//  TestOpenGL
//
//  Created by yafacex on 14-2-24.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef _MYOPENGLVIEW_H
#define _MYOPENGLVIEW_H

class MyOpenglView{
public:
    MyOpenglView(){};
    ~MyOpenglView(){};

    static MyOpenglView* getInstance(){
        if (!m_Instance) {
            m_Instance = new MyOpenglView();
        }
        return m_Instance;
    };
private:
    static MyOpenglView* m_Instance;
};

#endif
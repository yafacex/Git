//
//  MyOpenglView.m
//  TestOpenglView
//
//  Created by yafacex on 14-2-24.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#import "MyOpenglView.h"
#include "CppRender.h"
//#include "glYF.h"
@implementation MyOpenglView
- (void) drawRect:(NSRect)dirtyRect{
    [self initGL];
    [NSTimer scheduledTimerWithTimeInterval: 1.0/60
                                     target: self selector: @selector(update)
                                   userInfo: nil repeats:YES];
    [[self openGLContext]flushBuffer];
//    [[self openGLContext]makeCurrentContext];
    
}

- (void) update{
    CppRender::getInstance()->render();
//    [[self openGLContext] flushBuffer];
//    glFlush();
//    CGLContextObj* obj = (CGLContextObj*)[[self openGLContext]CGLContextObj];
//    CGLFlushDrawable(*obj);
//    glSwapAPPLE();

}
- (void) initGL{
    CppRender::getInstance()->init();
}

- (void) awakeFromNib
{
    NSOpenGLPixelFormatAttribute attrs[] =
    {
//        NSOpenGLPFADoubleBuffer,
//        NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)24,
        // Must specify the 3.2 Core Profile to use OpenGL 3.2
        NSOpenGLPFAOpenGLProfile,
        NSOpenGLProfileVersionLegacy,
//        NSOpenGLProfileVersion3_2Core,
        0
    };

    NSOpenGLPixelFormat *pf = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
 
    
    if (!pf)
    {
        NSLog(@"No OpenGL pixel format");
    }
    
    NSOpenGLContext* context = [[NSOpenGLContext alloc] initWithFormat:pf shareContext:nil] ;
    
    [self setPixelFormat:pf];
    
    [self setOpenGLContext:context];
    
    [[self openGLContext] makeCurrentContext];
    
}

@end

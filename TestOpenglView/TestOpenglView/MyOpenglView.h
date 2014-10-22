//
//  MyOpenglView.h
//  TestOpenglView
//
//  Created by yafacex on 14-2-24.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyOpenglView : NSOpenGLView{

}

- (void) drawRect:(NSRect)dirtyRect;
- (void) update;
- (void) initGL;



//-(id)initWithCoder:(NSCoder *)aDecoder;

@end

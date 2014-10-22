//
//  ViewController.m
//  TestOpenglES
//
//  Created by yafacex on 14-7-14.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#import "ViewController.h"
#include "Render.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// Uniform index.
enum
{
    UNIFORM_MODELVIEWPROJECTION_MATRIX,
    UNIFORM_NORMAL_MATRIX,
    NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

// Attribute index.
enum
{
    ATTRIB_VERTEX,
    ATTRIB_NORMAL,
    NUM_ATTRIBUTES
};

//GLfloat gCubeVertexData[216] = 
//{
//    // Data layout for each line below is:
//    // positionX, positionY, positionZ,     normalX, normalY, normalZ,
//    0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,
//    0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,
//    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
//    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
//    0.5f, 0.5f, -0.5f,          1.0f, 0.0f, 0.0f,
//    0.5f, 0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
//    
//    0.5f, 0.5f, -0.5f,         0.0f, 1.0f, 0.0f,
//    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
//    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
//    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
//    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
//    -0.5f, 0.5f, 0.5f,         0.0f, 1.0f, 0.0f,
//    
//    -0.5f, 0.5f, -0.5f,        -1.0f, 0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
//    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
//    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
//    -0.5f, -0.5f, 0.5f,        -1.0f, 0.0f, 0.0f,
//    
//    -0.5f, -0.5f, -0.5f,       0.0f, -1.0f, 0.0f,
//    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
//    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
//    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
//    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
//    0.5f, -0.5f, 0.5f,         0.0f, -1.0f, 0.0f,
//    
//    0.5f, 0.5f, 0.5f,          0.0f, 0.0f, 1.0f,
//    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
//    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
//    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
//    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
//    -0.5f, -0.5f, 0.5f,        0.0f, 0.0f, 1.0f,
//    
//    0.5f, -0.5f, -0.5f,        0.0f, 0.0f, -1.0f,
//    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
//    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
//    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
//    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
//    -0.5f, 0.5f, -0.5f,        0.0f, 0.0f, -1.0f
//};

@interface ViewController () {
    GLuint _program;
    
    GLKMatrix4 _modelViewProjectionMatrix;
    GLKMatrix3 _normalMatrix;
    float _rotation;
    
    GLuint _vertexArray;
    GLuint _vertexBuffer;
    
    Render render;
}
@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
}

- (void)dealloc
{    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    CSize size = {
        self.view.bounds.size.width,
        self.view.bounds.size.height
    };
    
    NSString* pp = [[NSBundle mainBundle] pathForAuxiliaryExecutable:@"./"];
    render.setup(size,pp.cString);
    
    return;
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteVertexArraysOES(1, &_vertexArray);
    
    self.effect = nil;
    
    render.tearDown();
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    render.update();
    return;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    return;
}

#pragma mark -  OpenGL ES 2 shader compilation

    
   

@end

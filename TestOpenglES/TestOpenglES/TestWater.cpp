//
//  TestWater.cpp
//  TestOpenglES
//
//  Created by yafacex on 14-7-14.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "TestWater.h"
#include "BWReader.h"
#include <math.h>

static int rgb;
static int translate = 1;
static int mesh = 1;
static float ttrans[2];
static float transx, transy, rotx, roty;
static float amplitude = 0.03;
static float freq = 5.0f;
static float phase = .00003;
static int ox = -1, oy = -1;
static int mot;
#define PAN	1
#define ROT	2

void TestWater::init(char *filename){
    GLfloat cloud_color[4] = { 1., 1., 1., 0., };
    GLfloat fog_color[4], fog_density = 0.05, density, far_cull;
    unsigned *image;
    int width, height, components;
	//  从文件中获取纹理数据
    if (filename)
	{
        BWReader reader;
		image = reader.read_texture(filename, &width, &height, &components);
		if (image == NULL)
		{
			fprintf(stderr, "Error: Can't load image file \"%s\".\n", filename);
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("%d x %d image loaded\n", width, height);
		}
		if (components < 3) rgb = 0;
    }
	//  由程序自动生成纹理数据
	else
	{
		int i, j;
		unsigned char *img;
		components = 4; width = height = 512;
		image = (unsigned *) malloc(width*height*sizeof(unsigned));
		img = (unsigned char *)image;
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++)
			{
				int w2 = width/2, h2 = height/2;
				if (i & 32)
					img[4*(i+j*width)+0] = 0xff;
				else
					img[4*(i+j*width)+1] = 0xff;
				if (j&32)
					img[4*(i+j*width)+2] = 0xff;
				if ((i-w2)*(i-w2) + (j-h2)*(j-h2) > 64*64 && (i-w2)*(i-w2) + (j-h2)*(j-h2) < 300*300)
					img[4*(i+j*width)+3] = 0xff;
			}
        
    }
	//  纹理参数的定义
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, cloud_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, components, width,
                 height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 image);
    glEnable(GL_TEXTURE_2D);
	// 使用雾
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    gluPerspective(50.,1.,.1,far_cull = 10.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.,0.,-5.5);
    
    density = 1.- expf(-5.5 * fog_density * fog_density *
                       far_cull * far_cull);
    
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
    density = MAX(MIN(density, 1.), 0.);
    
    fog_color[0] = .23 + density *.57;
    fog_color[1] = .35 + density *.45;
    fog_color[2] = .78 + density *.22;
    
    glClearColor(fog_color[0], fog_color[1], fog_color[2], 1.f);
    
    //fix me
//    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, fog_density);
    glFogfv(GL_FOG_COLOR, fog_color);
    if (fog_density > 0)
        glEnable(GL_FOG);
}

void TestWater::draw_mesh(void)
{
    //fix me
//    if (mesh)	//  以四边形模式进行绘制
//	{
//		glBegin(GL_QUADS);
//		glTexCoord2f(0, 0);
//        glVertex3f(-1.f, 0.f, -1.f);
//		glTexCoord2f(0, 1); glVertex3f(-1.f, 0.f,  1.f);
//		glTexCoord2f(1, 1); glVertex3f( 1.f, 0.f,  1.f);
//		glTexCoord2f(1, 0); glVertex3f( 1.f, 0.f, -1.f);
//		glEnd();
//    }
//	else		//  以多个三角形面片的形式进行绘制
//	{
//#define MESH 32
//		int i, j;
//		static float off;
//		float d = 1.f/MESH;
//		for(i = 0; i < MESH; i++)
//		{
//			glBegin(GL_TRIANGLE_STRIP);
//			for(j = 0; j < MESH; j++)
//			{
//				float s = (float)j*d;
//				float t = (float)i*d;
//				float x = -1.0 + 2.f*s;
//				float z = -1.0 + 2.f*t;
//				float y = amplitude*sinf(freq*2.f*M_PI*t+off);
//				glTexCoord2f(s, t); glVertex3f(x, y, z);
//				s += d; t += d;
//				x = -1.0 + 2.f*s;
//				z = -1.0 + 2.f*t;
//				y = amplitude*sinf(freq*2.f*M_PI*t+off);
//				glTexCoord2f(s, t); glVertex3f(x, y, z);
//				off += phase;
//			}
//			glEnd();
//		}
//    }
}

void TestWater::update(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glTranslatef(transx, transy, 0.f);
    glRotatef(rotx, 0., 1., 0.);
    glRotatef(roty, 1., 0., 0.);
    glScalef(10,1,10);
    //fix me
//    if (!rgb)
//		glColor3f(.31, .41, .97);
//    else
//		glColor3f(1.f,1.f,1.f);
//    glTranslatef(0.f,-1.f,0.f);
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glTranslatef(ttrans[0], ttrans[1], 0.);
    glScalef(10.f, 10.f,1.f);
    draw_mesh();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
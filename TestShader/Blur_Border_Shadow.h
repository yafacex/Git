/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2011 Ricardo Quesada
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

"											\n\
#ifdef GL_ES								\n\
precision lowp float;						\n\
#endif										\n\
											\n\
varying vec4 v_fragmentColor;				\n\
varying vec2 v_texCoord;					\n\
uniform sampler2D CC_Texture0;				\n\
vec2 adjacents[8];							\n\
varying vec2 v_texCoordOffs[5];						\n\
\n\
//the following three should be uniform,now for test\n\
float u_resolution;\n\
float u_radius;\n\
vec2 u_direction;\n\
float getGaussian2d(float x,float y,float o,float n){\n\
//g(x,y)= (  1 / (2*pi*¦Ò^2)  )  *   exp(   -(x-n/2)^2-(y-n/2)^2)/(2*¦Ò^2)  ) ;\n\
	float o2 = o * o;\n\
	x = x - n/2;\n\
	y = y - n/2;\n\
	return ( 1/(2*3.14*o2) * exp(-(x*x+y*y)/(2*o2)) );\n\
}\n\
void initAdjacents(){\n\
	float del = 1;//0.005;\n\
	adjacents[0] = vec2(-1,-1) * del;\n\
	adjacents[1] = vec2(-1,0) * del ;\n\
	adjacents[2] = vec2(-1,1) * del ;\n\
	adjacents[3] = vec2(0,-1) * del ;\n\
	adjacents[4] = vec2(0,1) * del ;\n\
	adjacents[5] = vec2(1,-1) * del;\n\
	adjacents[6] = vec2(1,0) * del;\n\
	adjacents[7] = vec2(1,1) * del;\n\
}\n\
void blur() {\n\
	u_resolution = 256;\n\
	u_radius = 1;\n\
	u_direction = vec2(0,0);\n\
	//this will be our RGBA sum\n\
	vec4 sum = vec4(0.0);\n\
	\n\
	//our original texcoord for this fragment\n\
	vec2 tc = v_texCoord;\n\
	\n\
	//the amount to blur, i.e. how far off center to sample from \n\
	//1.0 -> blur by one pixel\n\
	//2.0 -> blur by two pixels, etc.\n\
	float blur = u_radius/u_resolution; \n\
	\n\
	//the u_direction of our blur\n\
	//(1.0, 0.0) -> x-axis blur\n\
	//(0.0, 1.0) -> y-axis blur\n\
	float hstep = u_direction.x;\n\
	float vstep = u_direction.y;\n\
	\n\
	\n\
	//apply blurring, using a 9-tap filter with predefined gaussian weights\n\
	float n = 5;\n\
	float x=0;\n\
	float y=0;\n\
	float o = 1000000000;\n\
	float gs = 0;\n\
	float total = 0;\n\
	for(float i = 1-n ; i <= n ; ++i){\n\
		x = i; \n\
		y = n;\n\
		gs = getGaussian2d(x,y,o,n); \n\
		total += gs;\n\
		sum += texture2D(CC_Texture0, vec2(tc.x + x*blur, tc.y + y*blur)) * gs;\n\
	}\n\
	for(float i = n-1 ; i >= -n ; --i){\n\
		x = n; y = i;\n\
		gs = getGaussian2d(x,y,o,n); \n\
		total += gs;\n\
		sum += texture2D(CC_Texture0, vec2(tc.x + x*blur, tc.y + y*blur)) * gs;\n\
	}\n\
	for(float i = n-1 ; i >= -n ; --i){\n\
		x = i; y = -n;\n\
		gs = getGaussian2d(x,y,o,n); \n\
		total += gs;\n\
		sum += texture2D(CC_Texture0, vec2(tc.x + x*blur, tc.y + y*blur)) * gs;\n\
	}\n\
	for(float i = -n+1 ; i <= n ; ++i){\n\
		x = -n; y = i;\n\
		gs = getGaussian2d(x,y,o,n); \n\
		total += gs;\n\
		sum += texture2D(CC_Texture0, vec2(tc.x + x*blur, tc.y + y*blur)) * gs;\n\
	}\n\
	x = 0; y = 0;\n\
	gs = getGaussian2d(x,y,o,n); \n\
	total += gs;\n\
	sum += texture2D(CC_Texture0, vec2(tc.x + x*blur, tc.y + y*blur)) * gs;\n\
	sum *= 1 / total;\n\
	//discard alpha for our simple demo, multiply by vertex color and return\n\
	gl_FragColor = v_fragmentColor * vec4(sum.rgb, 1.0);\n\
}\n\
void border(){\n\
	vec4 pix;\n\
	float mul = 1.0;\n\
	vec4 onePix;\n\
	float sum = 0.0;\n\
	initAdjacents();\n\
	for (int i = 0; i < 8 ; ++i){\n\
		onePix = texture2D(CC_Texture0,v_texCoord+adjacents[i]);\n\
		mul = mul * onePix.a;\n\
		sum = sum + onePix.a;\n\
	}\n\
	pix = texture2D(CC_Texture0,v_texCoord);\n\
	if(mul == 0.0 && sum > 0.0){\n\
		pix = vec4(0,0,1,1);\n\
	}\n\
	gl_FragColor = v_fragmentColor * pix;//texture2D(CC_Texture0, v_texCoord);			\n\
}\n\
void shadowLefts(){\n\
	vec4 onePix;\n\
	vec4 frag = vec4(0);\n\
	for(int i=0;i<5;++i){\n\
		onePix = texture2D(CC_Texture0,v_texCoordOffs[i]);\n\
		onePix.a = (5-i)/5;\n\
		frag += onePix;\n\
	}\n\
	gl_FragColor = v_fragmentColor * frag;\n\
}\n\
void main()									\n\
{											\n\
	blur();\n\
	//border();\n\
	//shadowLefts();\n\
}											\n\
";

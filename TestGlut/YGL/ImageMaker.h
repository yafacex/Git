#include<GL/gl.h>
#include<math.h>
void makeImage(int w,int h,GLubyte* img){
    float totalDis = sqrt(w * w + h * h);
    for (int i = 0; i < w; ++i){
        for (int j = 0; j < h; ++j){
            float dis = sqrt(i * i + j * j);
            img[ i * 3 * w + j] = dis / totalDis * 255; 
            img[ i * 3 * w + j + 1] = dis / totalDis * 255; 
            img[ i * 3 * w + j + 2] = dis / totalDis * 255; 
        }        
    }    
}



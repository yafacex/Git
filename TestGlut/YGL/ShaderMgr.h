#include<GL/gl.h>
#include<stdio.h>
char* readFile(const char* fileName){
    FILE* fp = fopen(fileName,"r");
    if (fp) {
	    fseek(SEEK_END); 
	    long length = ftell(fp);
	    char* buffer = (char*)malloc(length*sizeof(char));
	    fseek(SEEK_SET);
	    fread(buffer,length,sizeof(char),fp);
	    return buffer;
    }else{
        return false;
    }
}


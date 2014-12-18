#include<GL/gl.h>
#include<stdio.h>

//read file support
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
        return NULL;
    }
}

//GlslProgram Support
typedef ShaderIndex GLuint;
typedef ProgramIndex GLuint;
struct GlslProgram
{
	ProgramIndex index;
	ShaderIndex* shaders;	
	long length;
};
GlslProgram* glslCreateProgram(){
	GlslProgram* gp = (GlslProgram*)malloc(sizeof(GlslProgram));
	gp->length = 0;
	gp->shaders = NULL;	
} 
GlslProgram* glslProgramAttach(GlslProgram* prog,ShaderIndex index){
	prog->shaders = (GlslProgram*)realloc(prog->length+1);
}

ShaderIndex glslCreateShader(){
	
}


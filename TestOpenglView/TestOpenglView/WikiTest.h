//
//  WikiTest.h
//  TestOpenglView
//
//  Created by yafacex on 14-5-26.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestOpenglView_WikiTest_h
#define TestOpenglView_WikiTest_h

class WikiTest{
public:
    WikiTest(){
        /*--------------------- Main OpenGL Program ---------------------*/
        
        /* Create a variable to hold the VBO identifier */
        GLuint triangleVBO;
        
        /* This is a handle to the shader program */
        GLuint shaderProgram;
        
        /* These pointers will receive the contents of our shader source code files */
        GLchar *vertexSource , *fragmentSource;
        vertexSource = (GLchar*)malloc(sizeof(GLchar)*300);
        fragmentSource = (GLchar*)malloc(sizeof(GLchar)*300);
        
        /* These are handles used to reference the shaders */
        GLuint vertexShader, fragmentShader;
        
        const unsigned int shaderAttribute = 0;
        
        const float NUM_OF_VERTICES_IN_DATA=3;
        
        /* Vertices of a triangle (counter-clockwise winding) */
        float data[3][3] = {
            {  0.0, 1.0, 0.0   },
            { -1.0, -1.0, 0.0  },
            {  1.0, -1.0, 0.0  }
        };
        
        /*---------------------- Initialise VBO - (Note: do only once, at start of program) ---------------------*/
        /* Create a new VBO and use the variable "triangleVBO" to store the VBO id */
        glGenBuffers(1, &triangleVBO);
        
        /* Make the new VBO active */
        glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
        
        /* Upload vertex data to the video device */
        glBufferData(GL_ARRAY_BUFFER, NUM_OF_VERTICES_IN_DATA * 3 * sizeof(float), data, GL_STATIC_DRAW);
        
        /* Specify that our coordinate data is going into attribute index 0(shaderAttribute), and contains three floats per vertex */
        glVertexAttribPointer(shaderAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        /* Enable attribute index 0(shaderAttribute) as being used */
        glEnableVertexAttribArray(shaderAttribute);
        
        /* Make the new VBO active. */
        glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
        /*-------------------------------------------------------------------------------------------------------*/
        
        /*--------------------- Load Vertex and Fragment shaders from files and compile them --------------------*/
        /* Read our shaders into the appropriate buffers */
        filetobuf("exampleVertexShader.vert",vertexSource);
        filetobuf("exampleFragmentShader.frag",fragmentSource);
        
        /* Assign our handles a "name" to new shader objects */
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        
        printf("%s\n",vertexSource);
        printf("%s\n",fragmentSource);
        /* Associate the source code buffers with each handle */
        glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
        glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
        
        /* Free the temporary allocated memory */
        free(vertexSource);
        free(fragmentSource);
        
        /* Compile our shader objects */
        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);
        /*-------------------------------------------------------------------------------------------------------*/
        
        /*-------------------- Create shader program, attach shaders to it and then link it ---------------------*/
        /* Assign our program handle a "name" */
        shaderProgram = glCreateProgram();
        
        /* Attach our shaders to our program */
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        
        /* Bind attribute index 0 (shaderAttribute) to in_Position*/
        /* "in_Position" will represent "data" array's contents in the vertex shader */
        glBindAttribLocation(shaderProgram, shaderAttribute, "in_Position");
        
        /* Link shader program*/
        glLinkProgram(shaderProgram);
        /*-------------------------------------------------------------------------------------------------------*/
        
        /* Set shader program as being actively used */
        glUseProgram(shaderProgram);
        
        /* Set background colour to BLACK */
        glClearColor(0.0, 0.0, 0.0, 1.0);
        
        /* Clear background with BLACK colour */
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* Actually draw the triangle, giving the number of vertices provided by invoke glDrawArrays
         while telling that our data is a triangle and we want to draw 0-3 vertexes 
         */
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /*---------------------------------------------------------------*/
    };
    
    void filetobuf(const char* file,GLchar* buffer){
        FILE* fp = fopen(file, "r");
        if (fp) {
            fread(buffer, sizeof(GLchar), 300, fp);
        }
        fclose(fp);
    }
    
};

#endif

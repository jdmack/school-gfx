#include <fstream>
#include <ios>
#include "GL/glut.h"
#include <string>
#include "shader.h"


unsigned long Shader::file_length(std::ifstream& file)
{
    if(!file.good()) return 0;
    
    unsigned long pos = file.tellg();
    file.seekg(0, std::ios::end);

    unsigned long len = file.tellg();
    file.seekg(std::ios::beg);
    
    return len;
}

int Shader::load_shader(char* filename, GLchar** ShaderSource, unsigned long & len)
{
   std::ifstream file;
   file.open(filename, std::ios::in); // opens as ASCII!

   if(!file) return -1;
    
   len = file_length(file);
    
   if(len == 0) return -2;   // Error: Empty File 
    
   *ShaderSource = (GLchar*) new char[len+1];
   if(*ShaderSource == 0) return -3;   // can't reserve memory
   
    // len isn't always strlen cause some characters are stripped in ascii read...
    // it is important to 0-terminate the real length later, len is just max possible value... 
   *ShaderSource[len] = 0; 

   unsigned int i = 0;
   while  (file.good()) {
       *ShaderSource[i] = file.get();       // get character from file.
       if(!file.eof())
        i++;
   }
    
   *ShaderSource[i] = 0;  // 0-terminate it at the correct position
    
   file.close();
      
   return 0; // No Error
}


int Shader::unload_shader(GLubyte** ShaderSource)
{
    if(*ShaderSource != 0)
        delete[] *ShaderSource;

   *ShaderSource = 0;
}

void Shader::init_shader()
{
    /*
    // Load source code
    //int Shader::load_shader(char* filename, GLchar** ShaderSource, unsigned long & len);

    std::string vertex_filename = "shaders/vertex_shader.txt";
    std::string fragment_filename = "shaders/fragment_shader.txt";

    GLchar** vertex_source;
    GLchar ** fragment_source;

    unsigned long v_file_length = 0;
    unsigned long f_file_length = 0;

    if(!load_shader(vertext_filename.c_str(), vertex_filename, v_file_length)) {
        // error
    }

    if(!load_shader(fragmentt_filename.c_str(), fragment_filename, f_file_length)) {
        // error
    }

    // Creates Shaders
    GLuint vertexShader, fragmentShader;

    vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

    // Attach source code
    glShaderSourceARB(vertexShaderObject, 1, &vertext_source, &v_file_length);
    glShaderSourceARB(fragmentShaderObject, 1, &fragment_source, &f_file_length);

    // Compile shaders
    glCompileShaderARB(vertexShaderObject);
    glCompileShaderARB(fragmentShaderObject);

    // Check compilation status
    GLint compiled;
    
    glGetObjectParameteriv(ShaderObject, GL_COMPILE_STATUS, &compiled);

    if(!compiled) {
        GLint blen = 0; 
        GLsizei slen = 0;

        glGetShaderiv(ShaderObject, GL_INFO_LOG_LENGTH , &blen);       

        if(blen > 1) {
            GLchar* compiler_log = (GLchar*)malloc(blen);
            glGetInfoLogARB(ShaderObject, blen, &slen, compiler_log);
            std::cout << "compiler_log:\n", compiler_log);
            free(compiler_log);
        }
    }        

    // Link shaders
    ProgramObject = glCreateProgram();

    glAttachShader(ProgramObject, vertexShaderObject);
    glAttachShader(ProgramObject, fragmentShaderObject);

    glLinkProgram(ProgramObject); 
    
    // Valid program object

    GLint linked;
    glGetProgramiv(ProgramObject, GL_LINK_STATUS, &linked);

    if(!linked) {
    }    
    */
}

void Shader::begin()
{
    //glUseProgram(ProgramObject);
   // CHECK_GL_ERROR();
}

void Shader::end()
{
    //glUseProgram(0);
    //CHECK_GL_ERROR();

}

#include <fstream>
#include <ios>
#include "GL/glut.h"
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
    // Compiler Shader

}



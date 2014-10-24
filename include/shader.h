#ifndef CSE_167_SHADER_H_
#define CSE_167_SHADER_H_

#include <fstream>

class Shader
{
    static unsigned long file_length(std::ifstream & file);
    static int load_shader(char* filename, GLchar** ShaderSource, unsigned long & len);
    static int unload_shader(GLubyte** ShaderSource);

    static void init_shader();
    static void begin();
    static void end();

};

#endif

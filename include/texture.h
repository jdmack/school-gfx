#ifndef CSE167_TEXTURE_H_
#define CSE167_TEXTURE_H_

#include <vector>

#include <GL/glut.h>

class Texture
{
    private:
        GLuint id_;
        //std::vector<Vector3> vertices_;

        GLuint load_texture(std::string);
        unsigned char * load_PPM(const char * filename, int & width, int & height);

    public:
        Texture();
        Texture(std::string filename);

        void bind();
        void unbind();




};


#endif

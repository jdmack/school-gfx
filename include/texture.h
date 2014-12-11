#ifndef CSE167_TEXTURE_H_
#define CSE167_TEXTURE_H_

#include <GL/glut.h>

class Texture
{
    private:

    public:
        static void load_texture();
        static unsigned char * load_PPM(const char * filename, int & width, int & height);



};


#endif

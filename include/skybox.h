#ifndef CSE167_SKYBOX_H_
#define CSE167_SKYBOX_H_

#include "shader.h"
#include "texture.h"
#include "object.h"

const std::string texture_front  = "texture/PalldioPalace_extern_front.ppm";
const std::string texture_back   = "texture/PalldioPalace_extern_back.ppm";
const std::string texture_left   = "texture/PalldioPalace_extern_left.ppm";
const std::string texture_right  = "texture/PalldioPalace_extern_right.ppm";
const std::string texture_top    = "texture/PalldioPalace_extern_top.ppm";
const std::string texture_bottom = "texture/PalldioPalace_extern_base.ppm";

enum face 
{ 
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM 
};

class Skybox : public Object
{
    private :
        double size_;

        bool facePresent[6];
        GLuint skyID;
        Texture * front_texture_;
        Texture * back_texture_;
        Texture * left_texture_;
        Texture * right_texture_;
        Texture * top_texture_;
        Texture * bottom_texture_;

        void create_cube_map(std::string front, std::string back, std::string top, std::string bottom, std::string left, std::string right, GLuint * tex_cube);
        void init();

        Shader *shader[5];
        Shader *skyShader;
        GLuint vao;
        GLuint SkyBoxVBO;

    public:
        Skybox(double radius);
        void update();
        void display();
        GLuint getSkyID();

};

#endif

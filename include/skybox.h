#ifndef CSE167_SKYBOX_H_
#define CSE167_SKYBOX_H_

#include <string>
#include "object.h"

#include <GL/glut.h>

const std::string texture_front  = "texture/desert_skybox_front.ppm";
const std::string texture_back   = "texture/desert_skybox_back.ppm";
const std::string texture_left   = "texture/desert_skybox_left.ppm";
const std::string texture_right  = "texture/desert_skybox_right.ppm";
const std::string texture_top    = "texture/desert_skybox_top.ppm";
const std::string texture_bottom = "texture/desert_skybox_bottom.ppm";

class Texture;
class Shader;

class Skybox : public Object
{
    private:
        float size_;
        bool use_map_;

        Texture * front_texture_;
        Texture * back_texture_;
        Texture * left_texture_;
        Texture * right_texture_;
        Texture * top_texture_;
        Texture * bottom_texture_;

        Shader * shader_;


        GLuint skybox[6];

        GLuint vbo;
        GLuint vao;

        void init();
        unsigned char * load_PPM(const char * filename, int & width, int & height);


    public:
        Skybox(float size);

        void set_shader(Shader * shader) { shader_ = shader; }
        Shader * shader() { return shader_; } 


        void create_cube_map(std::string front, std::string back, std::string top, std::string bottom, std::string left, std::string right, GLuint* tex_cube);

        void load_side(GLuint texture, GLenum side_target, std::string filename);

        GLuint getSkybox(int i) { return skybox[i]; }

        void display(Camera camera = Camera());
        void update();
};

#endif

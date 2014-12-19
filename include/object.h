#ifndef CSE167_OBJECT_H_
#define CSE167_OBJECT_H_

#include "matrix4.h"
#include "vector3.h"
#include "vector4.h"
#include "camera.h"
#include "color.h"
#include "material.h"
#include "shader.h"
#include "texture.h"

class Object
{
    protected:
        Matrix4 matrix_;
        Matrix4 matrix_obj_;
        Matrix4 matrix_o2w_;
        Vector3 position_;

        Matrix4 saved_obj_;
        Matrix4 saved_o2w_;

        Color color_;
        Material material_;
        Shader * shader_;
        Texture * texture_;

        bool visible_;

    public:
        // constructors
        Object();
        
        // accessors
        Matrix4& matrix() { return matrix_; } 
        Matrix4& matrix_obj() { return matrix_obj_; } 
        Matrix4& matrix_o2w() { return matrix_o2w_; } 
		Vector3& position() { return position_; }

        Color & color() { return color_; }
        Material & material() { return material_; }
        Shader * shader() { return shader_; }
        Texture * texture() { return texture_; }
       
        // mutators
        void set_color(Color color) { color_ = color; }
        void set_material(Material material) { material_ = material; }
        void set_shader(Shader * shader) { shader_ = shader; }
        void set_texture(Texture * texture) { texture_ = texture; }

        virtual void display(Camera camera = Camera());
        virtual void update(int ticks);
        virtual void reset();

        void save();
        void identity();
        void toggle_visible();

        void start_display(Camera camera);
        void end_display();
};

#endif


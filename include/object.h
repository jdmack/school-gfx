#ifndef CSE167_OBJECT_H_
#define CSE167_OBJECT_H_

#include "matrix4.h"
#include "vector3.h"
#include "vector4.h"
#include "camera.h"
#include "color.h"
#include "material.h"

class Object
{
    protected:
        Matrix4 matrix_;
        Matrix4 matrix_obj_;
        Matrix4 matrix_o2w_;
        double angle;
        Color color_;
        Material material_;
        int spin_;
        Vector3 position_;

    public:
        // constructors
        Object();
        
        // accessors
        Matrix4& matrix() { return matrix_; } 
        Matrix4& matrix_obj() { return matrix_obj_; } 
        Matrix4& matrix_o2w() { return matrix_o2w_; } 

        Color & color() { return color_; }
        Material & material() { return material_; }
       
        int get_spin() { return spin_; }
		Vector3& position() { return position_; }

        // mutators
        void set_color(Color color) { color_ = color; }
        void set_material(Material material) { material_ = material; }
        void set_spin(int spin) { spin_ = spin; }

        void spin(double);      // spin cube [degrees]
        void toggle_spin();

        virtual void display(Camera camera = Camera());
        virtual void update(int ticks);
        virtual void reset();
};

#endif


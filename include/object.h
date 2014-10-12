#ifndef CSE167_OBJECT_H_
#define CSE167_OBJECT_H_

#include "matrix4.h"
#include "vector4.h"

class Object
{
    protected:
        Matrix4 matrix_;
        Matrix4 spin_matrix_;
        Matrix4 rotate_matrix_;
        Matrix4 translate_matrix_;
        Matrix4 scale_matrix_;
        double angle;
        float red_;
        float green_;
        float blue_;
        int spin_;

    public:
        // constructors
        Object();
        
        // accessors
        Matrix4& matrix() { return matrix_; } 
        Matrix4& spin_matrix() { return spin_matrix_; }
        Matrix4& rotate_matrix() { return rotate_matrix_; } 
        Matrix4& translate_matrix() { return translate_matrix_; } 
        Matrix4& scale_matrix() { return scale_matrix_; } 
       
        float red() { return red_; }
        float green() { return green_; }
        float blue() { return blue_; }
        int get_spin() { return spin_; }

        // mutators
        void set_red(float red) { red_ = red; }
        void set_green(float green) { green_ = green; }
        void set_blue(float blue) { blue_ = blue; }
        void set_color(float red, float green, float blue);
        void set_spin(int spin) { spin_ = spin; }

        void spin(double);      // spin cube [degrees]
        void toggle_spin();
        void reset();

        virtual void display();
};

#endif


#ifndef CSE167_OBJECT_H_
#define CSE167_OBJECT_H_

#include "matrix4.h"
#include "vector3.h"
#include "vector4.h"

class Object
{
    protected:
        Matrix4 matrix_;
        Matrix4 matrix_obj_;
        Matrix4 matrix_o2w_;
        double angle;
        float red_;
        float green_;
        float blue_;
        int spin_;
        Vector3 position_;

    public:
        // constructors
        Object();
        
        // accessors
        Matrix4& matrix() { return matrix_; } 
        Matrix4& matrix_obj() { return matrix_obj_; } 
        Matrix4& matrix_o2w() { return matrix_o2w_; } 
       
        float red() { return red_; }
        float green() { return green_; }
        float blue() { return blue_; }
        int get_spin() { return spin_; }
		Vector3& position() { return position_; }

        // mutators
        void set_red(float red) { red_ = red; }
        void set_green(float green) { green_ = green; }
        void set_blue(float blue) { blue_ = blue; }
        void set_color(float red, float green, float blue);
        void set_spin(int spin) { spin_ = spin; }

        void spin(double);      // spin cube [degrees]
        void toggle_spin();

        virtual void display();
        virtual void update(int ticks);
        virtual void reset();
};

#endif


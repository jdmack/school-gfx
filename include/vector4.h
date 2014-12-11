#ifndef CSE167_VECTOR4_H_
#define CSE167_VECTOR4_H_

#include "matrix4.h"

class Matrix4;

class Vector4
{
    private:
        double x_;
        double y_;
        double z_;
        double w_;

    public:
        // constructors
        Vector4();
        // A constructor with three parameters for point coordinates
        Vector4(double x, double y, double z);
        // A constructor with four parameters
        Vector4(double x, double y, double z, double w);

        // accessors
        // Element access 'get': return one of the four coordinates
        double & x() { return x_; }
        double & y() { return y_; }
        double & z() { return z_; }
        double & w() { return w_; }
        double & get(int coordinate);
        double & get(char coordinate);

        // mutators
        // Element access 'set': set each coordinate separately
        void set_x(double x) { x_ = x; }
        void set_y(double y) { y_ = y; }
        void set_z(double z) { z_ = z; }
        void set_w(double w) { w_ = w; }
        void set_coordinates(double x, double y, double z, double w);
        void set(int coordinate, double value);

        // Overload operator '[]' as alternative to 'get' method
        double & operator[](int coordinate);
        double & operator[](char coordinate);

        // Vector addition
        void add(Vector4 param);

        // Overload operator '+' for addition
        Vector4 operator+(Vector4 param);

        // Vector subtraction
        void subtract(Vector4 param);

        // Overload operator '-' for subtraction
        Vector4 operator-(Vector4 param);

        double dot_product(Vector4 param);
        double operator*(Vector4 & param);

        Vector4 multiply(Matrix4 param);
        Vector4 operator*(Matrix4 & param);

        // Dehomogenize (make fourth component equal to 1)
        void dehomogenize();
        
        // Print (display the point's components numerically on the screen)
        void print();
};

#endif

#ifndef CSE167_VECTOR3_H_
#define CSE167_VECTOR3_H_

#include <string>
#include "matrix4.h"

class Vector3
{
    private:
        double x_;
        double y_;
        double z_;

    public:
        // constructors
        Vector3();
        // A constructor with three parameters for the vector coordinates
        Vector3(double x, double y, double z);

        // accessors
        // Element access 'get': return a specific coordinate of the vector
        double & x() { return x_; }
        double & y() { return y_; }
        double & z() { return z_; }
        double & get(int coordinate);
        double & get(char coordinate);

        // mutators
        // Element access 'set': set the vector coordinates
        void set_x(double x) { x_ = x; }
        void set_y(double y) { x_ = y; }
        void set_z(double z) { x_ = z; }
        void set(double x, double y, double z);

        // Overload operator '[]' as alternative to 'get' method
        double & operator[](int coordinate);
        double & operator[](char coordinate);

        // Vector addition
        void add(Vector3 param);

        // Overload operator '+' for addition
        Vector3 operator+(Vector3 param);

        // Vector subtraction
        void subtract(Vector3 param);

        // Overload operator '-' for subtraction
        Vector3 operator-(Vector3 param);

        // Negation
        void negate();

        // Scale (multiplication with scalar value)
        void scale(double param);

        // Dot product
        double dot_product(Vector3 param);

        // Cross product
        Vector3 cross_product(Vector3 param);

        // Magnitude (length of vector)
        double magnitude();

        // Normalize
        void normalize();

        void transform(Matrix4 param);

        // Print (display the vector's components numerically on the screen)
        void print();
        std::string str();
        double angle(Vector3 v);

};

#endif

#ifndef CSE167_MATRIX4_H_
#define CSE167_MATRIX4_H_

#include "vector4.h"
#define M_PI 3.14159265358979323846

class Vector4;

class Matrix4
{
    protected:
        double m_[4][4];   // matrix elements
        double m_col_[4][4];

    public:
        // constructors
        Matrix4();
        Matrix4(bool identity);
        Matrix4(const Matrix4 &param);
        // Constructor with 16 parameters to set the values of the matrix
        Matrix4(double, double, double, double,
                double, double, double, double,
                double, double, double, double,
                double, double, double, double);

        // 'get(x,y)' function to read any matrix element
        double get(int x, int y) const;

        void set(int x, int y, double value);
        void set(Matrix4 param);

        // Multiply (matrix-times-matrix)
        Matrix4 multiply(Matrix4 param);

        // Multiply (matrix-times-vector)
        Vector4 multiply(Vector4 param);

        Matrix4 operator*(Matrix4 & param);
        Vector4 operator*(Vector4 & param);

        // Make a rotation matrix about the x axis
        void rotate_x(double angle);

        // Make a rotation matrix about the y axis
        void rotate_y(double angle);

        // Make a rotation matrix about the z axis
        void rotate_z(double angle);

        // Make a rotation matrix about an arbitrary (unit) axis
        void rotate(double angle, Vector4 axis);

        // Make a non-uniform scaling matrix
        void scale(double x, double y, double z);

        // Make a translation matrix
        void translate(double x, double y, double z);

        // Print the matrix (display all 16 matrix components numerically on the screen in a 4x4 array)
        void print();

        // Transpose the matrix
        void transpose();

        double * pointer();
        double * pointer_col_major();
        void identity();

        void invert();

        void copy_3x3(Matrix4 param);
};

#endif

#include <iostream>
#include <cmath>
#include "vector4.h"

// constructors
Vector4::Vector4()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
    w_ = 1;
}

// A constructor with three parameters for point coordinates
Vector4::Vector4(double x, double y, double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = 1;
}

// A constructor with four parameters
Vector4::Vector4(double x, double y, double z, double w)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}

// accessors
// Element access 'get': return one of the four coordinates
double & Vector4::get(int coordinate)
{
    switch(coordinate) {
        case 0:
            return x_;
            break;
        case 1:
            return y_;
            break;
        case 2:
            return z_;
            break;
        case 3:
            return w_;
            break;
        default:
            return x_;
    }
}

double & Vector4::get(char coordinate)
{
    switch(coordinate) {
        case 'x':
            return x_;
            break;
        case 'y':
            return y_;
            break;
        case 'z':
            return z_;
            break;
        case 'w':
            return w_;
            break;
        default:
            return x_;
    }

}

// mutators
// Element access 'set': set the vector coordinates
void Vector4::set_coordinates(double x, double y, double z, double w)
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}
void Vector4::set(int coordinate, double value)
{
    switch(coordinate) {
        case 0:
            x_ = value;
            break;
        case 1:
            y_ = value;
            break;
        case 2:
            z_ = value;
            break;
        case 3:
            w_ = value;
            break;
    }
}

// Overload operator '[]' as alternative to 'get' method
double & Vector4::operator[](int coordinate)
{
    return get(coordinate);
}
double & Vector4::operator[](char coordinate)
{
    return get(coordinate);
}

// Vector addition
void Vector4::add(Vector4 param)
{
    x_ = x_ + param.x();
    y_ = y_ + param.y();
    z_ = z_ + param.z();
    w_ = w_ + param.w();
}

// Overload operator '+' for addition
Vector4 Vector4::operator+(Vector4 param)
{
    double new_x = x_ + param.x();
    double new_y = y_ + param.y();
    double new_z = z_ + param.z();
    double new_w = w_ + param.w();

    return Vector4(new_x, new_y, new_z, new_w);
}

// Vector subtraction
void Vector4::subtract(Vector4 param)
{
    x_ = x_ - param.x();
    y_ = y_ - param.y();
    z_ = z_ - param.z();
    w_ = w_ - param.w();
}

// Overload operator '-' for subtraction
Vector4 Vector4::operator-(Vector4 param)
{
    double new_x = x_ - param.x();
    double new_y = y_ - param.y();
    double new_z = z_ - param.z();
    double new_w = w_ - param.w();

    return Vector4(new_x, new_y, new_z, new_w);
}

// Dehomogenize (make fourth component equal to 1)
void Vector4::dehomogenize()
{
    // TODO: account for W = 0;
    x_ /= w_;
    y_ /= w_;
    z_ /= w_;
    w_ /= w_;
}

double Vector4::distance_from(Vector4 v)
{
    double xd = x_ - v.x();
    double yd = y_ - v.y();
    double zd = z_ - v.z();

    return std::sqrt(xd*xd + yd*yd + zd*zd);
}

// Dot product
double Vector4::dot_product(Vector4 param)
{
    double dot_product = (x_ * param.x())
                       + (y_ * param.y())
                       + (z_ * param.z())
                       + (w_ * param.w());

    return dot_product;
}

// Normalize
void Vector4::normalize()
{
    double magnitude = this->magnitude();
    x_ /= magnitude;
    y_ /= magnitude;
    z_ /= magnitude;
    w_ /= magnitude;
}

// Magnitude (length of vector)
double Vector4::magnitude()
{
    double magnitude = std::sqrt(std::pow(x_, 2)
        + std::pow(y_, 2)
        + std::pow(z_, 2)
        + std::pow(w_, 2)
        );

    return magnitude;
}
// Print (display the point's components numerically on the screen)
void Vector4::print()
{
    std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ", " << w_ << ")" << std::endl;
}

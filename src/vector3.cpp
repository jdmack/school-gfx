#include <iostream>
#include <cmath>
#include "vector3.h"

// constructors
Vector3::Vector3()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
}
// A constructor with three parameters for the vector coordinates
Vector3::Vector3(double x, double y, double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

// accessors
// Element access 'get': return a specific coordinate of the vector
double & Vector3::get(int coordinate)
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
        default:
            return x_;
    }
}

double & Vector3::get(char coordinate)
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
        default:
            return x_;
    }

}

// mutators
// Element access 'set': set the vector coordinates
void Vector3::set(double x, double y, double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

// Overload operator '[]' as alternative to 'get' method
double & Vector3::operator[](int coordinate)
{
    return get(coordinate);
}
double & Vector3::operator[](char coordinate)
{
    return get(coordinate);
}

// Vector addition
void Vector3::add(Vector3 param)
{
    x_ = x_ + param.x();
    y_ = y_ + param.y();
    z_ = z_ + param.z();
}

// Overload operator '+' for addition
Vector3 Vector3::operator+(Vector3 param)
{
    double new_x = x_ + param.x();
    double new_y = y_ + param.y();
    double new_z = z_ + param.z();
    
    return Vector3(new_x, new_y, new_z);
}

// Vector subtraction
void Vector3::subtract(Vector3 param)
{
    x_ = x_ - param.x();
    y_ = y_ - param.y();
    z_ = z_ - param.z();
}

// Overload operator '-' for subtraction
Vector3 Vector3::operator-(Vector3 param)
{
    double new_x = x_ - param.x();
    double new_y = y_ - param.y();
    double new_z = z_ - param.z();
    
    return Vector3(new_x, new_y, new_z);
}

// Negation
void Vector3::negate()
{
    x_ = -x_;
    y_ = -y_;
    z_ = -z_;
}

// Scale (multiplication with scalar value)
void Vector3::scale(double param)
{
    x_ *= param;
    y_ *= param;
    z_ *= param;
}

// Dot product
double Vector3::dot_product(Vector3 param)
{
    double dot_product = (x_ * param.x())
                       + (y_ * param.y())
                       + (z_ * param.z());

    return dot_product;
}

// Cross product
Vector3 Vector3::cross_product(Vector3 param)
{
    double new_x = ((y_ * param.z()) - (z_ * param.y()));
    double new_y = ((z_ * param.x()) - (x_ * param.z()));
    double new_z = ((x_ * param.y()) - (y_ * param.x()));
    
    return Vector3(new_x, new_y, new_z);
}

// Magnitude (length of vector)
double Vector3::magnitude()
{
    double magnitude = std::sqrt(std::pow(x_, 2) 
                               + std::pow(y_, 2) 
                               + std::pow(z_, 2)
                            );

    return magnitude;
}

// Normalize
void Vector3::normalize()
{
    double magnitude = this->magnitude();
    x_ /= magnitude;
    y_ /= magnitude;
    z_ /= magnitude;
}

// Print (display the vector's components numerically on the screen)
void Vector3::print()
{
    std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl;
}

double Vector3::angle(Vector3 v)
{
    double dot_product = this->dot_product(v);
    double this_mag    = this->magnitude();
    double v_mag       = v.magnitude();

    return std::acos(dot_product / (this_mag * v_mag));
}



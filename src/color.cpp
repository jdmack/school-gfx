#include "color.h"
#include <sstream>

Color::Color()
{
    r_ = 0;
    g_ = 0;
    b_ = 0;
}

Color::Color(double r, double g, double b)
{
    r_ = r;
    g_ = g;
    b_ = b;
}

Color Color::multiply(Color color)
{
    return Color(r_ * color.r(), g_ * color.g(), b_ * color.b());
}

Color Color::multiply(double param)
{
    return Color(r_ * param, g_ * param, b_ * param);
}

Color Color::divide(double param)
{
    return Color(r_ / param, g_ / param, b_ / param);
}

Color Color::operator*(Color color)
{
    return this->multiply(color);
}

Color Color::operator*(double param)
{
    return this->multiply(param);
}

Color Color::operator/(double param)
{
    return this->multiply(param);
}

std::string Color::str()
{
    std::stringstream ss;
    ss << "{" << r_ << ", " << g_ << ", " << b_ << ">";
    return ss.str();
}


#include <cmath>
#include "vector2.h"

Vector2::Vector2()
{
    x_component_ = 0;
    y_component_ = 0;

    direction_ = 0;
    magnitude_ = 0;

}
Vector2::Vector2(Point start, Point end)
{
    if(start == end) {
        x_component_ = 0;
        y_component_ = 0;

        direction_ = 0;
        magnitude_ = 0;

        return;
    }
    x_component_ = end.x() - start.x();
    y_component_ = end.y() - start.y();

    magnitude_ = sqrt(pow(x_component_, 2) + pow(y_component_, 2));

    if(x_component_ == 0) {
        if(y_component_ > 0) {
            direction_ = 90;
        }
        else {
            direction_ = 270;
        }

    }
    else if(y_component_ == 0) {
        if(x_component_ > 0) {
            direction_ = 0;
        }
        else {
            direction_ = 180;
        }
    }
    else {

        int quadrant = determine_quadrant(start, end);
        double theta = radians_to_degrees(acos(x_component_ / magnitude_));
        direction_ = determine_direction(quadrant, theta);
    }

    set_component_signs(direction_);
}

Vector2::Vector2(double magnitude, double direction)
{

    x_component_ = magnitude * cos(degrees_to_radians(direction));
    y_component_ = magnitude * sin(degrees_to_radians(direction));

    if(std::abs(x_component_) == magnitude) {
        y_component_ = 0;
    }
    if(std::abs(y_component_) == magnitude) {
        x_component_ = 0;
    }

    set_component_signs(direction);

    magnitude_ = magnitude;
    direction_ = direction;
}

double Vector2::radians_to_degrees(double radians)
{
    return radians / kPi * 180;
}

double Vector2::degrees_to_radians(double degrees)
{
    return degrees * kPi / 180;
}

int Vector2::determine_quadrant(Point start, Point end)
{
    if(end.x() > start.x()) {
        if(end.y() > start.y()) {
            // (+,+)
            return kQuadrantI;
        }
        else if(end.y() < start.y()) {
            // (+,-)
            return kQuadrantIV;
        }
    }
    else if(end.x() < start.x()) {
        if(end.y() > start.y()) {
            // (+,+)
            return kQuadrantII;
        }
        else if(end.y() < start.y()) {
            // (+,+)
            return kQuadrantIII;
        }
    }
    return 0;
}

void Vector2::set_component_signs(double direction)
{
    // Quadrant IV (+,-)
    if(direction > 270.0) {
        make_positive(x_component_);
        make_negative(y_component_);
    }
    // Quadrant III (-,-)
    else if(direction > 180.0) {
        make_negative(x_component_);
        make_negative(y_component_);
    }
    // Quadrant II (-,+)
    else if(direction > 90.0) {
        make_negative(x_component_);
        make_positive(y_component_);
    }
    // Quadrant I (+,+)
    else  {
        make_positive(x_component_);
        make_positive(y_component_);
    }
}

double Vector2::determine_direction(int quadrant, double theta)
{
    switch(quadrant) {
        case kQuadrantI:
            return theta;
            break;
        case kQuadrantII:
            return theta;
            break;
        case kQuadrantIII:
            return 360.0 - theta;
            break;
        case kQuadrantIV:
            return 360.0 - theta;
            break;
        default:
            return theta;
    }
}

void Vector2::make_positive(double & number)
{
    number = std::abs(number);
}

void Vector2::make_negative(double & number)
{
    number = std::abs(number) * -1;
}

void Vector2::flip_x()
{
    x_component_ *= -1;
}

void Vector2::flip_y()
{
    y_component_ *= -1;
}

Point::Point()
{
    // Default location is center of renderer
    x_ = 0;
    y_ = 0;
}

Point::Point(double x, double y)
{
    x_ = x;
    y_ = y;
}

bool Point::operator==(const Point &other) const
{
    if((x_ == other.x()) && (y_ == other.y())) {
        return true;
    }
    else {
        return false;
    }
}

bool Point::operator!=(const Point &other) const
{
    return !(*this == other);
}

double Point::distance_from(Point point)
{
    double x_distance = point.x() - x_;
    double y_distance = point.y() - y_;
    return sqrt((x_distance * x_distance) + (y_distance * y_distance));
}


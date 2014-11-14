#ifndef CSE167_VECTOR_H_
#define CSE167_VECTOR_H_

const double kPi = 3.141592653589793;
const double k90Degrees  = kPi / 2;
const double k180Degrees = kPi;
const double k270Degrees = 3 * k90Degrees;
const double k360Degrees = 2 * kPi;

const int kQuadrantI   = 1;
const int kQuadrantII  = 2;
const int kQuadrantIII = 3;
const int kQuadrantIV  = 4;

class Point
{
    private:
        double x_;
        double y_;
    public:
        Point();
        Point(double x, double y);

        // accessors
        double x() const { return x_; }
        double y() const { return y_; }

        // mutators
        void set_x(double x) { x_ = x; }
        void set_y(double y) { y_ = y; }

        bool operator==(const Point &other) const;
        bool operator!=(const Point &other) const;

        double distance_from(Point point);
};



class Vector2
{
    private:
        double direction_;
        double magnitude_;
        double x_component_;
        double y_component_;

    public:
        Vector2();
        Vector2(Point start, Point end);
        Vector2(double magnitude, double direction);

        // accessors
        double x_component() const { return x_component_; }
        double y_component() const { return y_component_; }
        double direction() const { return direction_; }
        double magnitude() const { return magnitude_; }

        double direction_r() { return direction_; }
        double direction_d() { return radians_to_degrees(direction_); }
        double radians_to_degrees(double radians);
        double degrees_to_radians(double degrees);

        void set_x_component(double x_component) { x_component_ = x_component; }
        void set_y_component(double y_component) { y_component_ = y_component; }

        int determine_quadrant(Point start, Point end);
        void set_component_signs(double direction);
        double determine_direction(int quadrant, double theta);
        void make_positive(double & number);
        void make_negative(double & number);

        void flip_x();
        void flip_y();


};

#endif

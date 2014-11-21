#ifndef CSE167_COLOR_H_
#define CSE167_COLOR_H_

#include <string>

class Color
{
    private:
        double r_;
        double g_;
        double b_;

    public:
        Color();
        Color(double r, double g, double b);

        double & r() { return r_; }
        double & g() { return g_; }
        double & b() { return b_; }

        void set_r(double r) { r_ = r; }
        void set_g(double g) { g_ = g; }
        void set_b(double b) { b_ = b; }


        Color multiply(Color color);
        Color multiply(double param);
        Color divide(double param);

        Color operator*(Color color);
        Color operator*(double param);
        Color operator/(double param);

        std::string str();
};

#endif
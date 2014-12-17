#ifndef CSE167_FLOOR_H_
#define CSE167_FLOOR_H_

#include "matrix4.h"
#include "object.h"
#include "camera.h"
#include "color.h"

const double kDefaultSize = 200;
const double kDefaultHeight = -10;
const Color kDefaultColor = Color(0.2, 0.2, 0.2);

class Floor : public Object
{
    private:
        double size_;
        double height_;
        Color color_;

    public:
        Floor();
        Floor(double size);

        double & size() { return size_; }
        void set_size(double size) { size_ = size; }

        double & height() { return height_; }
        void set_height(double height) { height_ = height; }

        Color & color() { return color_; }
        void set_color(Color color) { color_ = color; }

        void display(Camera camera = Camera());

        void update(int ticks);

};

#endif

#ifndef CSE_167_CUBE_H_
#define CSE_167_CUBE_H_

#include "matrix4.h"
#include "geode.h"

class Cube : public Geode
{
    private:
        double size_;

    public:
        Cube();
        //~Cube();

        // accessors
        double size() { return size_; }

        // mutators
        void set_size(double size) { size_ = size; }

        void draw(Matrix4 c);
        void update();
        void render();

};

#endif

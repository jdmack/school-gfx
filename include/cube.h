#ifndef CSE167_CUBE_H_
#define CSE167_CUBE_H_

#include "matrix4.h"
#include "vector4.h"
#include "object.h"
#include "camera.h"

const double kDefaultCubeSize = 10;

class Cube : public Object
{
    protected:
        double size_;
        
    public:
        // constructors
        Cube();
        Cube(double size);

        void display(Camera camera = Camera());
        void update(int ticks = 0);
};

#endif


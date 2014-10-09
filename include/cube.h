#ifndef CSE167_CUBE_H_
#define CSE167_CUBE_H_

#include "matrix4.h"

class Cube 
{
    protected:
        Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
        double angle;                   // rotation angle [degrees]

    public:
        Cube();                         // Constructor
        Matrix4 & getMatrix();
        void spin(double);              // spin cube [degrees]
};

#endif


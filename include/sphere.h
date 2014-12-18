#ifndef CSE167_SPHERE_H_
#define CSE167_SPHERE_H_

#include "matrix4.h"
#include "vector4.h"
#include "object.h"
#include "camera.h"

const double kDefaultSphereSize = 10;
const int kDefaultSphereSlices = 50;
const int kDefaultSphereStacks = 50;

class Sphere : public Object
{
    protected:
        double radius_;
        int slices_;
        int stacks_;
        
    public:
        // constructors
        Sphere();
        Sphere(double radius);

        void set_slices(int slices) { slices_ = slices; }
        void set_stacks(int stacks) { stacks_ = stacks; }

        void display(Camera camera = Camera());
        void update(int ticks = 0);
};

#endif


#ifndef CSE_167_SPHERE_H_
#define CSE_167_SPHERE_H_

#include "matrix4.h"
#include "geode.h"

const double kDefaultRadius = 1;
const int kDefaultSlices = 10;
const int kDefaultStacks = 10;

class Sphere : public Geode
{
    private:
        double radius_;
        int slices_;
        int stacks_;

    public:
        Sphere();
        Sphere(double radius, int slices = kDefaultSlices, int stacks = kDefaultStacks);

        // accessors
        double radius() { return radius_; }
        int slices() { return slices_; }
        int stacks() { return stacks_; }

        // mutators
        void set_radius(double radius) { radius_ = radius; }
        void set_slices(double slices) { slices_ = slices; }
        void set_stacks(double stacks) { stacks_ = stacks; }


        void draw(Matrix4 c);
        void update();
        void render();

};

#endif

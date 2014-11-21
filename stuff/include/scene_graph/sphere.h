#ifndef CSE167_SCENE_GRAPH_SPHERE_H_
#define CSE167_SCENE_GRAPH_SPHERE_H_

#include "matrix4.h"
#include "scene_graph/geode.h"

const double kDefaultRadius = 1;
const int kDefaultSlices = 50;
const int kDefaultStacks = 50;

class Sphere : public Geode
{
    private:
        double radius_;
        int slices_;
        int stacks_;

        double calc_radius();

    public:
        Sphere();
        Sphere(double radius, int slices = kDefaultSlices, int stacks = kDefaultStacks);

        // accessors
        double radius() { return radius_; }
        int slices() { return slices_; }
        int stacks() { return stacks_; }

        // mutators
        void set_radius(double radius) { radius_ = radius; }
        void set_slices(int slices) { slices_ = slices; }
        void set_stacks(int stacks) { stacks_ = stacks; }


        void draw(Matrix4 c);
        void update(int ticks);
        void render();

};

#endif

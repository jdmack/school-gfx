#ifndef CSE_167_NODE_H_
#define CSE_167_NODE_H_

#include <string>
#include "matrix4.h"
#include "vector3.h"

const int kDefaultBoundSlices = 50;
const int kDefaultBoundStacks = 50;

class Node
{
    protected:
        std::string name_;
        Vector3 center_point_;
        double bound_radius_;


    public:
        Node();
        ~Node();

        // accessors
        std::string name() { return name_; }

        // mutators
        void set_name(std::string name) { name_ = name; }

        virtual void draw(Matrix4 c) = 0;
        virtual void update(int ticks) = 0;
        virtual std::pair<Vector3, double> update_bound(Matrix4 c) = 0;

        void draw_bound();
};

#endif


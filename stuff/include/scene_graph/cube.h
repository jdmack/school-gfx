#ifndef CSE167_SCENE_GRAPH_CUBE_H_
#define CSE167_SCENE_GRAPH_CUBE_H_

#include "matrix4.h"
#include "scene_graph/geode.h"

const double kDefaultSize = 1;

class Cube : public Geode
{
    private:
        double size_;

        double calc_radius();

    public:
        Cube();
        Cube(double size);

        // accessors
        double size() { return size_; }

        // mutators
        void set_size(double size) { size_ = size; }

        void draw(Matrix4 c);
        void update(int ticks);
        void render();
    
};

#endif
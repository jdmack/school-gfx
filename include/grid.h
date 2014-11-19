#ifndef CSE_167_GRID_H_
#define CSE_167_GRID_H_

#include "matrix4.h"
#include "geode.h"


class Grid : public Geode
{
    private:

        double calc_radius();

    public:
        Grid();

        void draw(Matrix4 c);
        void update(int ticks);
        void render();
    
};

#endif

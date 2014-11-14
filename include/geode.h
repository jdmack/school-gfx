#ifndef CSE_167_GEODE_H_
#define CSE_167_GEODE_H_

#include "matrix4.h"
#include "node.h"

class Geode : public Node
{
    protected:
        virtual double calc_radius() = 0;

    public:
        Geode();
        //virtual ~Geode();
        
        void draw(Matrix4 c);
        virtual void update(int ticks);
        std::pair<Vector3, double> update_bound(Matrix4 c);

        virtual void render() = 0;
};

#endif

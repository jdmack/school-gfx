#ifndef CSE_167_GEODE_H_
#define CSE_167_GEODE_H_

#include "matrix4.h"
#include "node.h"

class Geode : public Node
{
    protected:

    public:
        Geode();
        //virtual ~Geode();
        
        virtual void draw(Matrix4 c) = 0;
        virtual void update() = 0;

        virtual void render() = 0;
};

#endif

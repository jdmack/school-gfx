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
        
        void draw(Matrix4 c);
        virtual void update();

        virtual void render() = 0;
};

#endif

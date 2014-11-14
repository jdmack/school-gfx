#ifndef CSE_167_NODE_H_
#define CSE_167_NODE_H_

#include "matrix4.h"

class Node
{
    protected:

    public:
        Node();
        ~Node();
        virtual void draw(Matrix4 c) = 0;
        virtual void update() = 0;

};

#endif


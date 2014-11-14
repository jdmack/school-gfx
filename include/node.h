#ifndef CSE_167_NODE_H_
#define CSE_167_NODE_H_

#include <string>
#include "matrix4.h"

class Node
{
    protected:
        std::string name_;
    public:
        Node();
        ~Node();

        // accessors
        std::string name() { return name_; }

        // mutators
        void set_name(std::string name) { name_ = name; }

        virtual void draw(Matrix4 c) = 0;
        virtual void update() = 0;

};

#endif


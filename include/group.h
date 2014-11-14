#ifndef CSE_167_GROUP_H_
#define CSE_167_GROUP_H_

#include <list>
#include "matrix4.h"
#include "node.h"

class Group : public Node
{
    protected:
        std::list<Node *> children_;

    public:
        Group();
        ~Group();

        void add_child(Node * node);
        void remove_child(Node * node);

        void draw(Matrix4 c);
        void update();

};

#endif

#ifndef CSE167_SCENE_GRAPH_GROUP_H_
#define CSE167_SCENE_GRAPH_GROUP_H_

#include <list>
#include "matrix4.h"
#include "scene_graph/node.h"

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
        void update(int ticks);
        std::pair<Vector3, double> update_bound(Matrix4 c);

};

#endif

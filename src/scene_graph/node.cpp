#include "globals.h"
#include "scene_graph/node.h"
#include <stdlib.h>
#include "GL/glut.h"

Node::Node()
{
    
}

Node::~Node()
{

}

void Node::draw_bound()
{
    //if(Globals::show_bound) {
        glMatrixMode(GL_MODELVIEW);
        Matrix4 matrix = Matrix4();
        matrix.identity();
        matrix.translate(center_point_.x(), center_point_.y(), center_point_.z());
        glLoadMatrixd(matrix.pointer());

        glColor3f(0.0, 1.0, 0.0);
        glutWireSphere(bound_radius_, kDefaultBoundSlices, kDefaultBoundStacks);
    //}


}

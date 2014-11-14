#include <iostream>
#include "matrix_transform.h"
#include "globals.h"
#include "frustum.h"

MatrixTransform::MatrixTransform()
{
    matrix_ = Matrix4();
    matrix_.identity();
}
MatrixTransform::MatrixTransform(Matrix4 matrix)
{
    matrix_ = matrix;
}

MatrixTransform::~MatrixTransform()
{

}
void MatrixTransform::draw(Matrix4 c)
{
    if(children_.size() > 1) {
        //draw_bound();
    }
    //if(Globals::frustum.sphereInFrustum(center_point_, bound_radius_)) {
        Group::draw(matrix_.multiply(c));
    //}
}

void MatrixTransform::update(int ticks)
{
    Group::update(ticks);
}

std::pair<Vector3, double> MatrixTransform::update_bound(Matrix4 c)
{
    
    std::pair<Vector3, double> sphere = Group::update_bound(matrix_.multiply(c));
    center_point_ = sphere.first;
    bound_radius_ = sphere.second;

    return sphere;
}

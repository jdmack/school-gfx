#include <iostream>
#include "matrix_transform.h"
#include "globals.h"

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
    // Should be good, don't touch!
    Group::draw(matrix_.multiply(c));
}

void MatrixTransform::update(int ticks)
{
    Group::update(ticks);
}

std::pair<Vector3, double> MatrixTransform::update_bound(Matrix4 c)
{
    
    Group::update_bound(matrix_.multiply(c));
    Vector3 center_point;
    double radius;
    std::pair<Vector3, double> sphere = std::make_pair(center_point, radius);
    return sphere;
}

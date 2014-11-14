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

void MatrixTransform::update()
{

}

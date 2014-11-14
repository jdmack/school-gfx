#include "matrix_transform.h"

MatrixTransform::MatrixTransform()
{

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
    Group::draw(matrix_.multiply(c));
}

void MatrixTransform::update()
{

}

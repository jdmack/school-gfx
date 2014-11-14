#include <iostream>
#include "GL/glut.h"
#include "cube.h"

Cube::Cube()
{
    size_ = kDefaultSize;
}

Cube::Cube(double size)
{
    size_ = size;
}

void Cube::draw(Matrix4 c)
{
    //std::cerr << name_ << " - Cube::draw()" << std::endl;
    Geode::draw(c);
    render();
}

void Cube::update()
{

}

void Cube::render()
{
    glutSolidCube(size_);
}

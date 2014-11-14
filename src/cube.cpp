#include <iostream>
#include <stdlib.h>
#include "GL/glut.h"
#include "cube.h"
#include "globals.h"

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
    if(Globals::frustum.sphereInFrustum(center_point_, bound_radius_)) {
        //std::cerr << "In frustum" << std::endl;
        Geode::draw(c);
        render();
    }
    else {
        //std::cerr << "Not in frustum" << std::endl;
    }
}

void Cube::update(int ticks)
{

}

void Cube::render()
{
    glColor3f(0.7, 0.7, 1.0);
    glutSolidCube(size_);
}

double Cube::calc_radius()
{
    return size_ / 2;
}


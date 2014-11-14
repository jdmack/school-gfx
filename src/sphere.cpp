#include <iostream>
#include "GL/glut.h"
#include "sphere.h"

Sphere::Sphere()
{

}

Sphere::Sphere(double radius, int slices, int stacks)
{
    radius_ = radius;
    slices_ = slices;
    stacks_ = stacks;
}

void Sphere::draw(Matrix4 c)
{
    Geode::draw(c);
    render();
}

void Sphere::update()
{

}

void Sphere::render()
{
    glutSolidSphere(radius_, slices_, stacks_);
}

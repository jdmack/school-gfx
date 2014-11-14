#include <iostream>
#include "GL/glut.h"
#include "sphere.h"

Sphere::Sphere()
{
    radius_ = kDefaultRadius;
    slices_ = kDefaultSlices;
    stacks_ = kDefaultStacks;
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

void Sphere::update(int ticks)
{

}

void Sphere::render()
{
    glutSolidSphere(radius_, slices_, stacks_);
}

double Sphere::calc_radius()
{
    return radius_;
}

#include <iostream>
#include <stdlib.h>
#include "GL/glut.h"
#include "scene_graph/geode.h"
#include "globals.h"
#include "matrix4.h"

Geode::Geode()
{

}

void Geode::draw(Matrix4 c)
{

    //std::cerr << name_ << " - Geode::draw()" << std::endl;
    glMatrixMode(GL_MODELVIEW);

    draw_bound();

    // Tell OpenGL what ObjectView matrix to use:
    glLoadMatrixd(c.pointer());
}

void Geode::update(int ticks)
{

}

std::pair<Vector3, double> Geode::update_bound(Matrix4 c)
{
    double radius = calc_radius();

    // calculate center point
    Vector4 cp4 = Vector4(0, 0, 0, 1);
    cp4 = c.multiply(cp4);
    center_point_ = Vector3(cp4.x(), cp4.y(), cp4.z());

    // calculate corner
    Vector4 corner4 = Vector4(radius, radius, radius, 1);
    corner4 = c.multiply(corner4);
    Vector3 corner = Vector3(corner4.x(), corner4.y(), corner4.z());

    bound_radius_ = corner.distance_from(center_point_);
    //std::cerr << "radius: " << bound_radius_ << std::endl;

    return std::make_pair(center_point_, bound_radius_);
}
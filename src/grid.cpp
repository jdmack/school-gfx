#include <iostream>
#include <stdlib.h>
#include "GL/glut.h"
#include "grid.h"
#include "globals.h"

Grid::Grid()
{
}

void Grid::draw(Matrix4 c)
{
    if(Globals::frustum.sphereInFrustum(center_point_, bound_radius_)) {
        Geode::draw(c);
        render();
    }
}

void Grid::update(int ticks)
{

}

void Grid::render()
{
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-30.0, -4.0, 200.0);
    glVertex3f(200.0, -4.0, 200.0);
    glVertex3f(200.0, -4.0, -50.0);
    glVertex3f(-30.0, -4.0, -50.0);
    glEnd();

}

double Grid::calc_radius()
{
    return 0;
}


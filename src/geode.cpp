#include <iostream>
#include "GL/glut.h"
#include "geode.h"
#include "globals.h"
#include "matrix4.h"

Geode::Geode()
{

}

void Geode::draw(Matrix4 c)
{
    //std::cerr << name_ << " - Geode::draw()" << std::endl;
    glMatrixMode(GL_MODELVIEW);

    // Tell OpenGL what ObjectView matrix to use:
    if(!Globals::flag) {
        c.print();
        Globals::flag = true;
    }
    glLoadMatrixd(c.pointer());

}

void Geode::update()
{

}
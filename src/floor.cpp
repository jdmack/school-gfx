#include <iostream>
#include <stdlib.h>

#include "floor.h"

#include "GL/glut.h"

Floor::Floor()
{
    size_ = kDefaultSize;
    color_ = kDefaultColor;
    height_ = kDefaultHeight;
}

Floor::Floor(double size)
{
    size_ = size;
    color_ = kDefaultColor;
    height_ = kDefaultHeight;
}

void Floor::update(int ticks)
{

}

void Floor::display(Camera camera)
{
    glBegin(GL_QUADS);

    glColor3f(color_.r(), color_.g(), color_.b());

    glNormal3f(0.0, 1.0, 0.0);

    glVertex3f(-size_, height_, size_ );
    glVertex3f(size_, height_, size_ );
    glVertex3f(size_, height_, -size_);
    glVertex3f(-size_, height_, -size_);
    glEnd();

}


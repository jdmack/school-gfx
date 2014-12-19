#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "cube.h"
#include "object.h"
#include "matrix4.h"
#include "camera.h"

#include <GL/glut.h>

Cube::Cube() : Object()
{
    size_ = kDefaultCubeSize;
}

Cube::Cube(double size) : Object()
{
    size_ = size;
}


void Cube::display(Camera camera)
{
    if(!visible_) return;

    Object::start_display(camera);
    glColor3f(0.0, 1.0, 0.0);

    //glutSolidCube(size_);
 // Draw all six faces of the cube:
    glBegin(GL_QUADS);

    glColor3f(0.0, 1.0, 0.0);       // This makes the cube green; the parameters are for red, green and blue.
    // To change the color of the other faces you will need to repeat this call before each face is drawn.

    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size_, size_, size_);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(size_, size_, size_);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(size_, -size_, size_);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-size_, -size_, size_);

    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size_, size_, size_);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-size_, size_, -size_);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-size_, -size_, -size_);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-size_, -size_, size_);

    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(size_, size_, size_);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(size_, size_, -size_);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(size_, -size_, -size_);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(size_, -size_, size_);

    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size_, size_, -size_);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(size_, size_, -size_);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(size_, -size_, -size_);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-size_, -size_, -size_);

    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size_, size_, size_);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(size_, size_, size_);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(size_, size_, -size_);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-size_, size_, -size_);

    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size_, -size_, -size_);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(size_, -size_, -size_);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(size_, -size_, size_);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-size_, -size_, size_);
    glEnd();


    Object::end_display();
}

void Cube::update(int ticks)
{
    double deg = 1.0;

    matrix_obj_.rotate_y(deg);
}

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

#include "cube.h"
#include "object.h"
#include "matrix4.h"
#include "camera.h"

Cube::Cube() : Object()
{
}


void Cube::display(Camera camera)
{
    glMatrixMode(GL_MODELVIEW);         // make sure we're in Objectview mode

    // Tell OpenGL what ObjectView matrix to use:

    matrix().identity();
    matrix().set(matrix().multiply(matrix_obj()));
    matrix().set(matrix().multiply(matrix_o2w()));
    matrix().set(matrix().multiply(camera.c()));
    glLoadMatrixd(matrix().pointer());

    // Draw all six faces of the cube:
    glBegin(GL_QUADS);

    glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue. 
    // To change the color of the other faces you will need to repeat this call before each face is drawn.

    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-5.0, 5.0, 5.0);
    glVertex3f(5.0, 5.0, 5.0);
    glVertex3f(5.0, -5.0, 5.0);
    glVertex3f(-5.0, -5.0, 5.0);

    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-5.0, 5.0, 5.0);
    glVertex3f(-5.0, 5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0, 5.0);

    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(5.0, 5.0, 5.0);
    glVertex3f(5.0, 5.0, -5.0);
    glVertex3f(5.0, -5.0, -5.0);
    glVertex3f(5.0, -5.0, 5.0);

    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-5.0, 5.0, -5.0);
    glVertex3f(5.0, 5.0, -5.0);
    glVertex3f(5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);

    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-5.0, 5.0, 5.0);
    glVertex3f(5.0, 5.0, 5.0);
    glVertex3f(5.0, 5.0, -5.0);
    glVertex3f(-5.0, 5.0, -5.0);

    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f(5.0, -5.0, -5.0);
    glVertex3f(5.0, -5.0, 5.0);
    glVertex3f(-5.0, -5.0, 5.0);
    glEnd();
}

void Cube::update(int ticks)
{
    spin(1.0);
}

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

#include "ball.h"
#include "object.h"
#include "matrix4.h"

Ball::Ball() : Object()
{
}


void Ball::display()
{
    glMatrixMode(GL_MODELVIEW);         // make sure we're in Objectview mode

    // Tell OpenGL what ObjectView matrix to use:

    matrix().identity();
    matrix().set(matrix().multiply(spin_matrix()));
    matrix().set(matrix().multiply(translate_matrix()));
    matrix().set(matrix().multiply(rotate_matrix()));
    matrix().set(matrix().multiply(scale_matrix()));
    glLoadMatrixd(matrix().pointer());

    // Draw sphere
    glutSolidSphere(5.0, 100.0, 100.0);
    
}
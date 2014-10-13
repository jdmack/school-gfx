#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "object.h"
#include "matrix4.h"

Object::Object()
{
    angle = 0.0;
    spin_ = 1;
    matrix_.identity();
    spin_matrix_.identity();
    translate_matrix_.identity();
    rotate_matrix_.identity();
    scale_matrix_.identity();
}

void Object::spin(double deg)
{
    angle += deg;
    if(angle > 360.0 || angle < -360.0) {
        angle = 0.0;
    }
    
    spin_matrix_.rotate_y(deg * spin_);
    //matrix_.rotate_y(deg * spin_);

}
void Object::set_color(float red, float green, float blue)
{
    set_red(red);
    set_green(green);
    set_blue(blue);
}

void Object::toggle_spin()
{
    spin_ *= -1;
}

void Object::reset()
{
    matrix_.identity();
    spin_matrix_.identity();
    rotate_matrix_.identity();
    translate_matrix_.identity();
    scale_matrix_.identity();
    set_color(0.0, 1.0, 0.0);
    position() = Vector3(0.0, 0.0, 0.0);

}

void Object::display()
{
    glMatrixMode(GL_MODELVIEW);         // make sure we're in Objectview mode

    // Tell OpenGL what ObjectView matrix to use:

    matrix().identity();
    matrix().set(matrix().multiply(spin_matrix()));
    matrix().set(matrix().multiply(translate_matrix()));
    matrix().set(matrix().multiply(rotate_matrix()));
    matrix().set(matrix().multiply(scale_matrix()));
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

void Object::update(int ticks)
{

}
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "object.h"
#include "matrix4.h"
#include "camera.h"

Object::Object()
{
    angle = 0.0;
    spin_ = 1;
    matrix_.identity();
    matrix_obj_.identity();
    matrix_o2w_.identity();
}

void Object::spin(double deg)
{
    angle += deg;
    if(angle > 360.0 || angle < -360.0) {
        angle = 0.0;
    }
    
    matrix_obj_.rotate_y(deg * spin_);

}

void Object::toggle_spin()
{
    spin_ *= -1;
}

void Object::reset()
{
    matrix_.identity();
    matrix_obj_.identity();
    matrix_o2w_.identity();
    set_color(Color(0.0, 1.0, 0.0));
    position() = Vector3(0.0, 0.0, 0.0);

}

void Object::display(Camera camera)
{

    start_display(camera);

// Draw stuff here

    end_display();

}

void Object::start_display(Camera camera)
{
    material_.enable();

    glMatrixMode(GL_MODELVIEW);         // make sure we're in Objectview mode

    // Tell OpenGL what ObjectView matrix to use:

    glPushMatrix();

    matrix().identity();
    matrix().set(matrix().multiply(matrix_obj()));
    matrix().set(matrix().multiply(matrix_o2w()));
    matrix().set(matrix().multiply(camera.c()));
    glLoadMatrixd(matrix().pointer());
    

}

void Object::end_display()
{
    glPopMatrix();
}

void Object::update(int ticks)
{

}

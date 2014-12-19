#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "object.h"
#include "matrix4.h"
#include "camera.h"

#include <GL/glut.h>

Object::Object()
{
    matrix_.identity();
    matrix_obj_.identity();
    matrix_o2w_.identity();

    shader_ = nullptr;
    texture_ = nullptr;

    visible_ = true;

}

void Object::reset()
{
    matrix_.identity();
    //matrix_obj_.identity();
    //matrix_o2w_.identity();
    matrix_obj_ = saved_obj_;
    matrix_o2w_ = saved_o2w_;
    set_color(Color(0.0, 1.0, 0.0));

    position() = Vector3(0.0, 0.0, 0.0);
    visible_ = true;

}

void Object::identity()
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
    if(shader_ != nullptr) shader_->bind();
    if(texture_ != nullptr) texture_->bind();


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
    if(texture_ != nullptr) texture_->unbind();
    if(shader_ != nullptr) shader_->unbind();

    glPopMatrix();
}

void Object::update(int ticks)
{
    
}

void Object::save()
{
    saved_obj_ = matrix_obj_; 
    saved_o2w_ = matrix_o2w_; 
}

void Object::toggle_visible()
{
    visible_ = !visible_;
}

#include <iostream>
#include <stdlib.h>
#include "GL/glut.h"
#include "light.h"
#include "matrix4.h"

Light::Light()
{
    number_ = 0;

    enabled_ = false;

    set_position(0.0, 0.0, 1.0, 1.0);

    set_ambient(0.0, 0.0, 0.0, 1.0);
    set_diffuse(1.0, 1.0, 1.0, 1.0);
    set_specular(1.0, 1.0, 1.0, 1.0);

    constant_atten_[0] = 1.0;
    linear_atten_[0] = 0.0;
    quadratic_atten_[0] = 0.0;
}

Light::Light(int number)
{
    number_ = number;

    enabled_ = false;

    set_position(0.0, 0.0, 1.0, 1.0);

    set_ambient(0.0, 0.0, 0.0, 1.0);
    set_diffuse(1.0, 1.0, 1.0, 1.0);
    set_specular(1.0, 1.0, 1.0, 1.0);

    constant_atten_[0] = 1.0;
    linear_atten_[0] = 0.0;
    quadratic_atten_[0] = 0.0;
}

void Light::set_ambient(float a, float b, float c, float d)
{
    ambient_[0] = a;
    ambient_[1] = b;
    ambient_[2] = c;
    ambient_[3] = d;
}

void Light::set_specular(float a, float b, float c, float d)
{
    specular_[0] = a;
    specular_[1] = b;
    specular_[2] = c;
    specular_[3] = d;
}

void Light::set_diffuse(float a, float b, float c, float d)
{
    diffuse_[0] = a;
    diffuse_[1] = b;
    diffuse_[2] = c;
    diffuse_[3] = d;
}

void Light::set_position(float x, float y, float z, float w)
{
    std::cerr << "setting position: " << x << ", " << y << ", " << z << ", " << w << std::endl; 
    position_[0] = x;
    position_[1] = y;
    position_[2] = z;
    position_[3] = w;
}

void Light::enable()
{
    std::cerr << "Light " << number_ << " enabled" << std::endl;
    //std::cerr << "Light " << number_ << " set" << std::endl;
    Matrix4 matrix(true);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(matrix.pointer());

    //std::cerr << "ambient: " << ambient_[0] << ", " << ambient_[1] << ", " << ambient_[2] << ", " << ambient_[3] << std::endl; 
    //std::cerr << "diffuse: " << diffuse_[0] << ", " << diffuse_[1] << ", " << diffuse_[2] << ", " << diffuse_[3] << std::endl; 
    //std::cerr << "specular_: " << specular_[0] << ", " << specular_[1] << ", " << specular_[2] << ", " << specular_[3] << std::endl; 

    glLightfv(GL_LIGHT0 + number_, GL_AMBIENT, ambient_);
    glLightfv(GL_LIGHT0 + number_, GL_DIFFUSE, diffuse_);
    glLightfv(GL_LIGHT0 + number_, GL_SPECULAR, specular_);
    glLightfv(GL_LIGHT0 + number_, GL_POSITION, position_);
    glLightfv(GL_LIGHT0 + number_, GL_CONSTANT_ATTENUATION, constant_atten_);
    glLightfv(GL_LIGHT0 + number_, GL_LINEAR_ATTENUATION, linear_atten_);
    glLightfv(GL_LIGHT0 + number_, GL_QUADRATIC_ATTENUATION, quadratic_atten_);
    glEnable(GL_LIGHT0 + number_);
    enabled_ = true;

}

void Light::disable()
{
    std::cerr << "Light " << number_ << " disabled" << std::endl;
    enabled_ = false;
    glDisable(GL_LIGHT0 + number_);
}

void Light::display()
{
    if(!enabled_) return;

    Matrix4 matrix(true);
    matrix.translate(position_[0], position_[1], position_[2]);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(matrix.pointer());
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.2, 50, 50);
}

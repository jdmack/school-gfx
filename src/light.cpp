#include "GL/glut.h"
#include "light.h"

Light::Light()
{
    number_ = 0;

    enabled_ = false;

    ambient_[0] = 0.2;
    ambient_[1] = 0.2;
    ambient_[2] = 0.2;
    ambient_[3] = 1.0;

    diffuse_[0] = 0.8;
    diffuse_[1] = 0.8;
    diffuse_[2] = 0.8;
    diffuse_[3] = 1.0;

    specular_[0] = 0.0;
    specular_[1] = 0.0;
    specular_[2] = 0.0;
    specular_[3] = 1.0;

    position_[0] = 0.0;
    position_[1] = 10.0;
    position_[2] = 1.0;
    position_[3] = 0.0;
}

Light::Light(int number)
{
    number_ = number;

    enabled_ = false;

    ambient_[0] = 0.2;
    ambient_[1] = 0.2;
    ambient_[2] = 0.2;
    ambient_[3] = 1.0;

    diffuse_[0] = 0.8;
    diffuse_[1] = 0.8;
    diffuse_[2] = 0.8;
    diffuse_[3] = 1.0;

    specular_[0] = 0.0;
    specular_[1] = 0.0;
    specular_[2] = 0.0;
    specular_[3] = 1.0;

    position_[0] = 0.0;
    position_[1] = 10.0;
    position_[2] = 1.0;
    position_[3] = 0.0;
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

void Light::set_position(float a, float b, float c, float d)
{
    position_[0] = a;
    position_[1] = b;
    position_[2] = c;
    position_[3] = d;
}

void Light::enable()
{
    enabled_ = true;
    glLightfv(GL_LIGHT0 + number_, GL_AMBIENT, ambient_);
    glLightfv(GL_LIGHT0 + number_, GL_DIFFUSE, diffuse_);
    glLightfv(GL_LIGHT0 + number_, GL_SPECULAR, specular_);
    glLightfv(GL_LIGHT0 + number_, GL_POSITION, position_);

    glEnable(GL_LIGHT0 + number_);
}

void Light::disable()
{
    enabled_ = false;
    glDisable(GL_LIGHT0 + number_);
}


#include <iostream>
#include <stdlib.h>
#include "GL/glut.h"
#include "spot_light.h"
#include "light.h"
#include "matrix4.h"

SpotLight::SpotLight() : Light()
{
    std::cerr << "SpotLight()" << std::endl;
    set_direction(0.0, 0.0, -1.0);
    set_exponent(0.0);
    set_cutoff(180.0);
}

SpotLight::SpotLight(int number) : Light(number)
{
    std::cerr << "SpotLight(int)" << std::endl;
    set_direction(0.0, 0.0, -1.0);
    set_exponent(0.0);
    set_cutoff(180.0);
}

void SpotLight::set_direction(float x, float y, float z)
{
    direction_[0] = x;
    direction_[1] = y;
    direction_[2] = z;
}


void SpotLight::enable()
{
    std::cerr << "Light " << number_ << " enabled" << std::endl;

    Matrix4 matrix(true);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(matrix.pointer());

    glLightfv(GL_LIGHT0 + number_, GL_SPOT_DIRECTION, direction_);
    glLightfv(GL_LIGHT0 + number_, GL_SPOT_EXPONENT, exponent_);
    glLightfv(GL_LIGHT0 + number_, GL_SPOT_CUTOFF, cutoff_);

    Light::enable();

}


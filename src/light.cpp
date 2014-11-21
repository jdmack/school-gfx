#include "GL/glut.h"
#include "light.h"
#include "struct.h"


Light::Light()
{
    number_ = 0;
    ambient_ = float4(0.2, 0.2, 0.2, 1.0);
    diffuse_ = float4(0.8, 0.8, 0.8, 1.0);
    specular_ = float4(0.0, 0.0, 0.0, 1.0);
    position_ = float4(0.0, 10.0, 1.0, 0.0);
}

Light::Light(int number)
{
    number_ = number;
    ambient_ = float4(0.2, 0.2, 0.2, 1.0);
    diffuse_ = float4(0.8, 0.8, 0.8, 1.0);
    specular_ = float4(0.0, 0.0, 0.0, 1.0);
    position_ = float4(0.0, 10.0, 1.0, 0.0);
}

void Light::render()
{
    glLightfv(GL_LIGHT0 + number_, GL_AMBIENT, ambient_.val);
    glLightfv(GL_LIGHT0 + number_, GL_DIFFUSE, diffuse_.val);
    glLightfv(GL_LIGHT0 + number_, GL_SPECULAR, specular_.val);
    glLightfv(GL_LIGHT0 + number_, GL_POSITION, position_.val);

    glEnable(GL_LIGHT0 + number_);
}
#include "GL/glut.h"
#include "material.h"

Material::Material()
{
    ambient_ = float4(0.2, 0.2, 0.2, 1.0);
    diffuse_ = float4(0.8, 0.8, 0.8, 1.0);
    specular_ = float4(0.0, 0.0, 0.0, 1.0);
    shininess_ = float1(0.0);
    emission_ = float4(0.0, 0.0, 0.0, 1.0);
}

Material::Material(float4 ambient, float4 diffuse, float4 specular, float1 shininess, float4 emission)
{
    ambient_ = ambient;
    diffuse_ = diffuse;
    specular_ = specular;
    shininess_ = shininess;
    emission_ = emission;
}

void Material::render()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_.val);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_.val);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_.val);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess_.val);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission_.val);
}
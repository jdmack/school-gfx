#include <stdlib.h>
#include "GL/glut.h"
#include "material.h"
#include <iostream>

Material::Material()
{
    set_ambient(0.2, 0.2, 0.2, 1.0);
    set_diffuse(0.8, 0.8, 0.8, 1.0);
    set_specular(0.0, 0.0, 0.0, 1.0);
    set_shininess(0.0);
    set_emission(0.0, 0.0, 0.0, 1.0);
}

void Material::set_ambient(float a, float b, float c, float d)
{
    ambient_[0] = a;
    ambient_[1] = b;
    ambient_[2] = c;
    ambient_[3] = d;
}

void Material::set_diffuse(float a, float b, float c, float d)
{
    diffuse_[0] = a;
    diffuse_[1] = b;
    diffuse_[2] = c;
    diffuse_[3] = d;
}

void Material::set_specular(float a, float b, float c, float d)
{
    specular_[0] = a;
    specular_[1] = b;
    specular_[2] = c;
    specular_[3] = d;
}

void Material::set_shininess(float a)
{
    shininess_[0] = a;
}

void Material::set_emission(float a, float b, float c, float d)
{
    emission_[0] = a;
    emission_[1] = b;
    emission_[2] = c;
    emission_[3] = d;
}

void Material::set_ambient(float * ambient)
{
    set_ambient(ambient[0], ambient[1], ambient[2], ambient[3]); 
}

void Material::set_diffuse(float * diffuse)
{
    set_diffuse(diffuse[0], diffuse[1], diffuse[2], diffuse[3]); 
}

void Material::set_specular(float * specular)
{
    set_specular(specular[0], specular[1], specular[2], specular[3]); 
}

void Material::set_shininess(float * shininess)
{
    set_shininess(shininess[0]);
}

void Material::set_emission(float * emission)
{
    set_emission(emission[0], emission[1], emission[2], emission[3]); 
}

void Material::enable()
{
    //float ambient[] = {0.2, 0.2, 0.2, 1.0};
    //float diffuse[] = {0.8, 0.8, 0.8, 1.0};
    //float specular[] = {0.8, 0.8, 0.8, 1.0};
    //float shininess[] = {0.0}; 
    //float emission[] = {0.0, 0.0, 0.0, 1.0};

    //glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    //glMaterialfv(GL_FRONT, GL_EMISSION, emission);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess_);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission_);
}

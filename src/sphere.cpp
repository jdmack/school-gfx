#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "sphere.h"
#include "object.h"
#include "matrix4.h"
#include "camera.h"

#include <GL/glut.h>

Sphere::Sphere() : Object()
{
    radius_ = kDefaultSphereSize;
    slices_ = kDefaultSphereSlices;
    stacks_ = kDefaultSphereStacks;
}

Sphere::Sphere(double radius) : Object()
{
    radius_ = radius;
    slices_ = kDefaultSphereSlices;
    stacks_ = kDefaultSphereStacks;
}


void Sphere::display(Camera camera)
{
    Object::start_display(camera);

    glColor3f(0.0, 1.0, 0.0);

    glutSolidSphere(radius_, slices_, stacks_);

    Object::end_display();
}

void Sphere::update(int ticks)
{
    // Spin code
    //double deg = 1.0;
    //matrix_obj_.rotate_y(deg);
}

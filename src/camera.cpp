#include "camera.h"
#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"

Camera::Camera()
{
    reset();
}

Camera::Camera(Vector3 e, Vector3 d, Vector3 up)
{
    e_ = e;
    d_ = d;
    up_ = up;
    calc();
}

void Camera::reset()
{
    //c_.identity();
    e_.set(0,0,10);
    d_.set(0,0,0);
    up_.set(0,1,0);
    calc();
    //c_.translate(0, 0, -10);
}

double * Camera::gl_matrix()
{
    //return c_.pointer_col_major();
    return c_.pointer();
}

void Camera::calc() 
{
    Vector3 z = e_ - d_;
    z.scale(1.0 / z.magnitude());

    Vector3 x = (up_.cross_product(z));
    x.scale(1.0 / x.magnitude());

    Vector3 y = z.cross_product(x);

    c_ = Matrix4(x.get(0), y.get(0), z.get(0), e_.get(0),
                 x.get(1), y.get(1), z.get(1), e_.get(1),
                 x.get(2), y.get(2), z.get(2), e_.get(2),
                      0.0,      0.0,      0.0,     1.0);
    // transpose puts it in column major ordering
    c_.transpose();

    //c_.translate(0, 0, -20);

    // invert because we need to multiple by camera inverse 
    c_.invert();
}

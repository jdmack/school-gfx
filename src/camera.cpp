#include "camera.h"
#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"

Camera::Camera()
{
    c_.identity();
}

Camera::Camera(Vector3 e, Vector3 d, Vector3 up)
{
    e_ = e;
    d_ = d;
    up_ = up;

    Vector3 z = e - d;
    z.scale(1.0 / z.magnitude());

    Vector3 x = (up.cross_product(z));
    x.scale(1.0 / x.magnitude());

    Vector3 y = z.cross_product(x);

    c_ = Matrix4(x.get(0), y.get(0), z.get(0), e.get(0),
                 x.get(1), y.get(1), z.get(1), e.get(1),
                 x.get(2), y.get(2), z.get(2), e.get(2),
                      0.0,      0.0,      0.0,     1.0);

    /*
    std::cout << "z: ";
    z.print();
    std::cout << std::endl;

    std::cout << "x: ";
    x.print();
    std::cout << std::endl;

    std::cout << "y: ";
    y.print();
    std::cout << std::endl;

    std::cout << "c: \n";
    c_.print();
    std::cout << std::endl;
    */
    
}

void Camera::reset()
{
    c_.identity();
    e_.set(0,0,0);
    d_.set(0,0,0);
    up_.set(0,1,0);
}

double * Camera::gl_matrix()
{
    //return c_.pointer_col_major();
    return c_.pointer();
}

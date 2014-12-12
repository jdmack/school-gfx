#include "model.h"

#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "trackball.h"
#include "vector3.h"
#include "window.h"
#include "globals.h"
#include "triangle.h"

#include "GL/glut.h"

MouseMovement Trackball::movement = NONE;
Vector3 Trackball::last_point = Vector3();
Matrix4 Trackball::rotation = Matrix4(true);
Matrix4 Trackball::scaling = Matrix4(true);



void Trackball::mouse_move(int x, int y)
{
    //std::cerr << "===================================================================================" << std::endl;
    //std::cerr << "Mouse moving: (" << x << "," << y << ") -" << std::endl;

    Vector3 direction = Vector3();
    double pixel_diff;
    double rot_angle, zoom_factor;
    double velocity;
    Triangle point_at;

    Vector3 rotate_axis3;
    Vector4 rotate_axis4;
    Vector3 cur_point;

    switch(movement) {
        case ROTATE:
            //std::cerr << "ROTATE" << std::endl;

            //std::cerr << "cur_point: " << cur_point.str() << std::endl;
            //std::cerr << "last_point: " << last_point.str() << std::endl;

            cur_point = trackball_mapping(x, y);

            direction = cur_point - last_point;
            velocity = direction.magnitude();

            //std::cerr << "velocity: " << velocity << std::endl;

            if(velocity > 0.001) {
                //rotate_axis3 = last_point.cross_product(cur_point);
                rotate_axis3 = cur_point.cross_product(last_point);
                rotate_axis3.normalize();
                rot_angle = velocity * kRotateScale;
                //std::cerr << "rotate_axis: " << rotate_axis3.str() << std::endl;
                //std::cerr << "rot_angle: " << rot_angle << std::endl;
                
                rotate_axis4 = Vector4(rotate_axis3.x(), rotate_axis3.y(), rotate_axis3.z(), 0);

                rotation.identity();
                rotation.rotate(rot_angle, rotate_axis4);
                //rotation = rotate_matrix * rotation;
                //rotation = rotate_matrix;
                //std::cerr << "rotation matrix: " << std::endl;
                //rotation.print();
                //Globals::focus->matrix_o2w() = Globals::focus->matrix_obj().multiply(rotation);
                Globals::focus->matrix_o2w() = Globals::focus->matrix_o2w().multiply(rotation);
            }
            break;
        case ZOOM:
            cur_point = Vector3(x, y, 0);
            pixel_diff = cur_point.x() - last_point.x();
            zoom_factor = 1.0 + pixel_diff * kZoomScale;

            scaling.identity();
            scaling.scale(zoom_factor, zoom_factor, zoom_factor);
            Globals::focus->matrix_obj() = Globals::focus->matrix_obj().multiply(scaling);
            //scaling = scaling * s;
            //scaling_mt->setMatrix(scaling);
            //displayCallback();

            break;

        case NONE:

            break;
    }

    last_point = cur_point;
}


void Trackball::mouse_func(int button, int state, int x, int y)
{
    if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        //std::cerr << "Left click" << std::endl;
        movement = ROTATE;
        //old_x = x;
        //old_y = y;
        last_point = trackball_mapping(x, y);
    }
    else if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
        //std::cerr << "Right click" << std::endl;
        movement = ZOOM;
        //old_x = x;
        //old_y = y;
        //last_point = trackball_mapping(x, y);
        last_point = Vector3(x, y, 0);
    }
    else {
        movement = NONE;
    }
}


Vector3 Trackball::trackball_mapping(int x, int y)
{
    double width = (double) GWindow::width;
    double height = (double) GWindow::height;

    double d_x = (double) x;
    double d_y = (double) y;

    //std::cerr << "width: " << width << std::endl;
    //std::cerr << "height: " << height << std::endl;

    Vector3 v = Vector3();
    double new_x = (2.0 * d_x - width) / width;
    double new_y = - (height - 3.0 * d_y) / height;
    //std::cerr << "new_x: " << new_x << std::endl;
    //std::cerr << "new_y: " << new_y << std::endl;

    v.set_x(new_x);
    v.set_y(new_y);
    v.set_z(0.0);
    //std::cerr << "v: " << v.str() << std::endl;

    double d = v.magnitude();
    //std::cerr << "d: " << d << std::endl;

    //if(d <= 1.0) {
    //    d = 1.0;
    //}
    d = (d < 1.0) ? d : 1.0;

    v.set_z(std::sqrt(1.001 - d * d));
    v.normalize();
    
    //std::cerr << "trackball_mapping() returning: " << v.str() << std::endl;

    return v;
}

bool Trackball::rayIntersectsTriangle(Vector3 p, Vector3 v0, Vector3 v1, Vector3 v2) 
{

    Vector3 d = Vector3(0, 0, 1);
    Vector3 e1, e2, h, s, q;
    float a, f, u, v;
    float t;
    e1 = Vector3(v1 - v0);
    e2 = Vector3(v2 - v0);

    h = d.cross_product(e2);
    a = e1.dot_product(h);

    if (a > -0.00001 && a < 0.00001)
        return(false);

    f = 1 / a;
    s = Vector3(p - v0);
    u = f * (s.dot_product(h));

    if (u < 0.0 || u > 1.0)
        return(false);

    q = s.cross_product(e1);
    v = f * d.dot_product(q);

    if (v < 0.0 || u + v > 1.0)
        return(false);

    // at this stage we can compute t to find out where
    // the intersection point is on the line
    t = f * e2.dot_product(q);

    if(t > 0.00001)  {// ray intersection
        std::cerr << "Found: (" << v0.str() << ", " <<  v1.str() << ", " << v2.str() << ")" << std::endl;
        return(true);
    }

    else // this means that there is a line intersection
         // but not a ray intersection
         return (false);
}

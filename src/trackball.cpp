#include <stdlib.h>
#include <iostream>
#include "GL/glut.h"
#include "trackball.h"
#include "vector3.h"
#include "window.h"
#include "globals.h"

MouseMovement Trackball::movement = NONE;
Vector3 Trackball::last_point = Vector3();
Matrix4 Trackball::rotation = Matrix4();
Matrix4 Trackball::scaling = Matrix4();



void Trackball::mouse_move(int x, int y)
{
    std::cerr << "===================================================================================" << std::endl;
    std::cerr << "Mouse moving: (" << x << "," << y << ") -" << std::endl;

    Vector3 direction = Vector3();
    double pixel_diff;
    double rot_angle, zoom_factor;
    double velocity;

    Vector3 rotate_axis3;
    Vector4 rotate_axis4;
    Matrix4 rotate_matrix;
    Vector3 cur_point;
    cur_point = trackball_mapping(x, y);

    switch(movement) {
        case ROTATE:
            std::cerr << "ROTATE" << std::endl;

            std::cerr << "cur_point: " << cur_point.str() << std::endl;
            std::cerr << "last_point: " << last_point.str() << std::endl;

            //cur_point = trackball_mapping(x, y);
            direction = cur_point - last_point;
            velocity = direction.magnitude();

            std::cerr << "velocity: " << velocity << std::endl;

            if(velocity > 0.0001) {
                rotate_axis3 = last_point.cross_product(cur_point);
                rotate_axis3.normalize();
                rot_angle = velocity * kRotateScale;
                std::cerr << "rotate_axis: " << rotate_axis3.str() << std::endl;
                
                rotate_axis4 = Vector4(rotate_axis3.x(), rotate_axis3.y(), rotate_axis3.z(), 0);

                rotate_matrix.identity();
                rotate_matrix.rotate(rot_angle, rotate_axis4);
                rotation = rotate_matrix * rotation;
                Globals::focus->matrix_obj().multiply(rotation);
            }
            break;
        case ZOOM:
            /*
            pixel_diff = cur_point[1] - last_point[1];
            zoom_factor = 1.0 + pixel_diff * ZOOMSCALE;
            Matrix4 s;
            s.scale(zoom_factor, zoom_factor, zoom_factor);
            scaling = scaling * s;
            scaling_mt->setMatrix(scaling);
            displayCallback();
            */
        break;
    }

    last_point = cur_point;
}


void Trackball::mouse_func(int button, int state, int x, int y)
{
    if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        std::cerr << "Left click" << std::endl;
        movement = ROTATE;
        //old_x = x;
        //old_y = y;
        last_point = trackball_mapping(x, y);
    }
    else if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
        std::cerr << "Right click" << std::endl;
        movement = ZOOM;
        //old_x = x;
        //old_y = y;
        last_point = trackball_mapping(x, y);
    }
    else {
        movement = NONE;
    }
}


Vector3 Trackball::trackball_mapping(int x, int y)
{
    //double width = (double) Window::width;
    //double height = (double) Window::height;

    double width = 512.0;
    double height = 512.0;

    double d_x = (double) x;
    double d_y = (double) y;

    std::cerr << "width: " << width << std::endl;
    std::cerr << "height: " << height << std::endl;

    Vector3 v = Vector3();
    double new_x = (2.0 * d_x - width) / width;
    double new_y = (height - 2.0 * d_y) / height;
    std::cerr << "new_x: " << new_x << std::endl;
    std::cerr << "new_y: " << new_y << std::endl;



    v.set_x(new_x);
    v.set_y(new_y);
    v.set_z(0.0);
    std::cerr << "v: " << v.str() << std::endl;

    double d = v.magnitude();
    std::cerr << "d: " << d << std::endl;

    if(d <= 1.0) {
        d = 1.0;
    }

    v.set_z(std::sqrt(1.001 - d * d));
    //v.normalize();
    std::cerr << "v: " << v.str() << std::endl;
    
    std::cerr << "trackball_mapping() returning: " << v.str() << std::endl;

    return v;
}
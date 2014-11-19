#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glut.h>

#include "window.h"
#include "matrix4.h"
#include "globals.h"
#include "timer.h"
#include "cube.h"
#include "matrix_transform.h"
#include "robot.h"
#include "sphere.h"
#include "grid.h"

#define kPi 3.14159265359

// TODO:
// - Camera has to be transposed and inverted to work right, fix this


void keyboard_callback(unsigned char key, int x, int y);
void keyboard_special_callback(int key, int x, int y);
void setup();

int main(int argc, char *argv[])
{
    float specular[]  = {1.0, 1.0, 1.0, 1.0};
    float shininess[] = {100.0};
    float position[]  = {0.0, 10.0, 1.0, 0.0};	    // lightsource position

    Window::timer_.start();

    glutInit(&argc, argv);      	      	        // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
    
    glutInitWindowSize(Window::width, Window::height);      // set initial window size
    glutCreateWindow("CSE167 Project");    	        // open window and set window title

    glEnable(GL_DEPTH_TEST);            	        // enable depth buffering
    //glEnable(GL_NORMALIZE);            	            
    glClear(GL_DEPTH_BUFFER_BIT);       	        // clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);   	        // set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      // set polygon drawing mode to fill front and back of each polygon
    
    glDisable(GL_CULL_FACE);                        // disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);             	        // set shading to smooth
    glMatrixMode(GL_PROJECTION); 
  
    // Generate material properties:
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // Round points
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    // Generate light source:
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
  
    // Install callback functions:
    glutDisplayFunc(Window::display_callback);
    glutReshapeFunc(Window::reshape_callback);
    glutIdleFunc(Window::idle_callback);
    
    // Set keyboard callback functions
    glutKeyboardFunc(keyboard_callback);
    glutSpecialFunc(keyboard_special_callback);

    setup();

    glutMainLoop();
    return 0;
}

//----------------------------------------------------------------------------
// 
void keyboard_callback(unsigned char key, int x, int y)
{
    Vector3 camera_pos;
    Vector3 camera_look_at;
    switch (key) {
        case 'b':
            Globals::show_bound = !Globals::show_bound;
			break;

        case 'c':
            Globals::culling = !Globals::culling;
			break;

        case 'p':
            Globals::pause = !Globals::pause;
			break;

        case 's':
            Globals::root->matrix().scale(0.9, 0.9, 0.9);
			break;

        case 'S':
            Globals::root->matrix().scale(1.1, 1.1, 1.1);
			break;

        case 'x':
            Globals::root->matrix().rotate_x(10);
			break;

        case 'X':
            Globals::root->matrix().rotate_x(-10);
			break;

        case 'y':
            Globals::root->matrix().rotate_y(10);
			break;

        case 'Y':
            Globals::root->matrix().rotate_y(-10);
			break;

        case 'z':
            Globals::root->matrix().rotate_z(10);
			break;

        case 'Z':
            Globals::root->matrix().rotate_z(-10);
			break;


        case 'a':
			break;

        case 'd':
			break;

		case 32: // spacebar
			break;

		case 27:
			exit(0);
			break;
    }

}

void keyboard_special_callback(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_LEFT:
            Globals::root->matrix().translate(1, 0, 0);
            break;

        case GLUT_KEY_RIGHT:
            Globals::root->matrix().translate(-1, 0, 0);
            break;

        case GLUT_KEY_UP:
            Globals::root->matrix().translate(0, 0, -1);
            break;

        case GLUT_KEY_DOWN:
            Globals::root->matrix().translate(0, 0, 1);
            break;


        // F1 - Display Cube
        case GLUT_KEY_F1:

            break;

        // F2 - Display House View 1
        case GLUT_KEY_F2:

            break;

        // F3 - Display House View 2
        case GLUT_KEY_F3:

            //Globals::camera.set_e(Vector3(-15, 5, 10));
            //Globals::camera.set_d(Vector3(-5, 0, 0));
            //Globals::camera.set_up(Vector3(0, 1, 0.5));
            //Globals::camera.calc();

            break;

        // F4 - Display Bunny
        case GLUT_KEY_F4:

            break;

        // F5 - Display Dragon
        case GLUT_KEY_F5:

            break;

        // F6
        case GLUT_KEY_F6:
            break;

        // F8
        case GLUT_KEY_F8:
            break;

        // F9
        case GLUT_KEY_F9:
            break;
    }
}

void setup()
{
    int number_of_rows = 10;
    int number_of_columns = 10;

    int row_width = 20;
    int column_width = 20;

    Globals::identity_matrix.identity();
    Matrix4 matrix = Matrix4();
    matrix.identity();

    MatrixTransform * root = new MatrixTransform(matrix);
    root->set_name("root");
    Globals::root = root;

    Grid * grid = new Grid();
    root->add_child(grid);
    for(int row = 0; row < number_of_rows; row++) {
        for(int column = 0; column < number_of_columns; column++) {

            Robot * robot = new Robot();

            matrix.identity();
            matrix.scale(0.4, 0.4, 0.4);
            matrix.translate(column_width * column, 4.0, row_width * row);
            //matrix.rotate_y(45);

            MatrixTransform * mt_robot = new MatrixTransform(matrix);
            mt_robot->add_child(robot);

            //Sphere * sphere = new Sphere(2, 50, 50);
            //root->add_child(sphere);

            root->add_child(mt_robot);
        }
    }

    /*
    Robot * robot = new Robot();
    matrix.identity();
    //matrix.scale(0.0, 0.0, 0.0);
    //matrix.translate(0.0, 0.0, 0.0);
    //matrix.rotate_y(45);

    MatrixTransform * mt_robot = new MatrixTransform(matrix);
    mt_robot->add_child(robot);

    //Sphere * sphere = new Sphere(2, 50, 50);
    //root->add_child(sphere);

    root->add_child(mt_robot);
    */
}

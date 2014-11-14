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

    //Globals::focus = static_cast<Object *>(&Globals::cube);
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
        case 'w':
			break;

        case 's':
			break;

        case 'a':
			break;

        case 'd':
			break;

		case 'x': 
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
    Matrix4 matrix = Matrix4();

    Group * root = new Group();
    root->set_name("root");
    Globals::root = root;

    matrix.identity();
    matrix.translate(0.0, 8.0, 0.0);
   //matrix.rotate_y(90);

    MatrixTransform * robot = new MatrixTransform(matrix);
    root->set_name("robot");

    Cube * head = new Cube();
    Cube * torso = new Cube();
    Cube * left_arm = new Cube();
    Cube * right_arm = new Cube();
    Cube * left_leg = new Cube();
    Cube * right_leg = new Cube();

    MatrixTransform * mt_head;
    MatrixTransform * mt_torso;
    MatrixTransform * mt_left_arm;
    MatrixTransform * mt_right_arm;
    MatrixTransform * mt_left_leg;
    MatrixTransform * mt_right_leg;

    // HEAD
    matrix.identity();
    matrix.print();
    matrix.scale(3.0, 3.0, 3.0);
    matrix.translate(0.0, 0.0, 0.0);
    
    mt_head = new MatrixTransform(matrix);
    mt_head->add_child(head);

    robot->add_child(mt_head);

    // TORSO
    matrix.identity();
    matrix.scale(5.0, 8.0, 2.0);
    matrix.translate(0.0, -6.0, 0.0);
    
    mt_torso = new MatrixTransform(matrix);
    mt_torso->add_child(torso);

    robot->add_child(mt_torso);

    // LEFT ARM
    matrix.identity();
    matrix.scale(1.0, 8.0, 1.0);
    matrix.translate(3.4, -6.0, 0.0);
    
    mt_left_arm = new MatrixTransform(matrix);
    mt_left_arm->add_child(left_arm);

    robot->add_child(mt_left_arm);

    // RIGHT ARM
    matrix.identity();
    matrix.scale(1.0, 8.0, 1.0);
    matrix.translate(-3.4, -6.0, 0.0);
    
    mt_right_arm = new MatrixTransform(matrix);
    mt_right_arm->add_child(right_arm);

    robot->add_child(mt_right_arm);

    // LEFT LEG
    matrix.identity();
    matrix.scale(2.0, 8.0, 2.0);
    matrix.translate(1.7, -14.5, 0.0);
    
    mt_left_leg = new MatrixTransform(matrix);
    mt_left_leg->add_child(left_leg);

    robot->add_child(mt_left_leg);

    // RIGHT LEG
    matrix.identity();
    matrix.scale(2.0, 8.0, 2.0);
    matrix.translate(-1.7, -14.5, 0.0);
    
    mt_right_leg = new MatrixTransform(matrix);
    mt_right_leg->add_child(right_leg);

    robot->add_child(mt_right_leg);


    root->add_child(robot);

}






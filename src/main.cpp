#include "glee.h"
#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glut.h>

#include "window.h"
#include "matrix4.h"
#include "globals.h"
#include "timer.h"
#include "model.h"
#include "trackball.h"
#include "light.h"
#include "vector4.h"
#include "skybox.h"

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
    //float position[]  = {0.0, 10.0, 1.0, 0.0};	    // lightsource position

    GWindow::timer_.start();

    glutInit(&argc, argv);      	      	        // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
    
    glutInitWindowSize(GWindow::width, GWindow::height);      // set initial window size
    glutCreateWindow("CSE167 Project");    	        // open window and set window title

    glEnable(GL_DEPTH_TEST);            	        // enable depth buffering
    glEnable(GL_NORMALIZE);            	            
    glClear(GL_DEPTH_BUFFER_BIT);       	        // clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 1.0);   	        // set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      // set polygon drawing mode to fill front and back of each polygon

    // NEW STUFF FROM TEXTURE
    glEnable(GL_TEXTURE_2D);   // enable texture mapping
    glClearDepth(1.0f);        // depth buffer setup
    glEnable(GL_DEPTH_TEST);   // enables depth testing
    glDepthFunc(GL_LEQUAL);    // configure depth testing
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // really nice perspective calculations

    
    glDisable(GL_CULL_FACE);                        // disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);             	        // set shading to smooth
    glMatrixMode(GL_PROJECTION); 
  
    // Generate material properties:
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // Generate light source:
    //glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    //glEnable(GL_LIGHT0);
  
    // Install callback functions:
    glutDisplayFunc(GWindow::display_callback);
    glutReshapeFunc(GWindow::reshape_callback);
    glutIdleFunc(GWindow::idle_callback);
    
    // Set keyboard callback functions
    glutKeyboardFunc(keyboard_callback);
    glutSpecialFunc(keyboard_special_callback);

    // Set mouse functions
    glutMouseFunc(Trackball::mouse_func);
    glutMotionFunc(Trackball::mouse_move);

    setup();

    glutMainLoop();
    return 0;
}

//----------------------------------------------------------------------------
// 
void keyboard_callback(unsigned char key, int x, int y)
{
    Vector4 axis(0, 1, 0, 0);
    Vector3 camera_pos;
    Vector3 camera_look_at;
    switch (key) {
        case 'r':
            Globals::focus->reset();
			break;

        case 'c':
            Globals::focus->matrix_o2w().rotate(10, axis);
			break;

        //case 'p':
        //    Globals::pause = !Globals::pause;
	    //    break;

        case 's':
            Globals::focus->matrix_obj().scale(0.9, 0.9, 0.9);
			break;

        case 'S':
            Globals::focus->matrix_obj().scale(1.1, 1.1, 1.1);
			break;

        case 'x':
            Globals::focus->matrix_o2w().translate(-1.0, 0.0, 0.0);
            break;

        case 'X':
            Globals::focus->matrix_o2w().translate(1.0, 0.0, 0.0);
            break;

        case 'y':
            Globals::focus->matrix_o2w().translate(0.0, -1.0, 0.0);
            break;

        case 'Y':
            Globals::focus->matrix_o2w().translate(0.0, 1.0, 0.0);
            break;

        case 'z':
            Globals::focus->matrix_o2w().translate(0.0, 0.0, -1.0);
            break;

        case 'Z':
            Globals::focus->matrix_o2w().translate(0.0, 0.0, 1.0);
            break;

        case 'j':
            Globals::focus->matrix_o2w().rotate_x(10);
			break;

        case 'E':
            Globals::focus->matrix_o2w().rotate_x(-10);
			break;

        case 't':
            Globals::focus->matrix_o2w().rotate_y(10);
			break;

        case 'T':
            Globals::focus->matrix_o2w().rotate_y(-10);
			break;

        case 'o':
            Globals::focus->matrix_o2w().rotate_z(10);
			break;

        case 'O':
            Globals::focus->matrix_o2w().rotate_z(-10);
			break;

        case 'p':
            Globals::focus->shader()->toggle();
			break;


        case 'a':
			break;

        case 'l':
			break;

        case '1':
            if(Globals::light1->enabled()) {
                Globals::light1->disable();
            }
            else {
                Globals::light1->enable();
            }
            break;

        case '2':
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
            
            break;

        case GLUT_KEY_RIGHT:
            break;

        case GLUT_KEY_UP:
            break;

        case GLUT_KEY_DOWN:
            break;

        case GLUT_KEY_F1:
            break;

        case GLUT_KEY_F2:

            break;

        case GLUT_KEY_F3:

            break;

        case GLUT_KEY_F4:

            break;

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
    //Globals::focus = Globals::bunny;

    // setup shaders
    Shader * bunny_shader = new Shader("shader/spot_light.vert", "shader/spot_light.frag", true);
    bunny_shader->set_active(false);
    //Globals::bunny->set_shader(bunny_shader);

    // setup bezier
    Vector3 control_p[16];

    control_p[0] = Vector3(-20, 0, 20);
    control_p[1] = Vector3(-7, -3, 20);
    control_p[2] = Vector3(7, -4, 20);
    control_p[3] = Vector3(20, 0, 20);
    control_p[4] = Vector3(-20, -2, 7);
    control_p[5] = Vector3(-7, 0, 7);
    control_p[6] = Vector3(7, -2, 7);
    control_p[7] = Vector3(20, -1, 7);
    control_p[8] = Vector3(-20, -4, -7);
    control_p[9] = Vector3(-7, -2, -7);
    control_p[10] = Vector3(7, -3, -7);
    control_p[11] = Vector3(20, -2, -7);
    control_p[12] = Vector3(-20, 0, -20);
    control_p[13] = Vector3(-7, -2, -20);
    control_p[14] = Vector3(7, -2, -20);
    control_p[15] = Vector3(20, 0, -20);

    Globals::bezier_patch = new BezierPatch(control_p, 150, 150);
    Globals::skybox = new Skybox(20);

    Globals::light1 = new Light(0);
    Globals::light1->set_position(-3.0, 3.0, 0.0, 1.0);
    Globals::light1->set_ambient(0.0, 0.0, 0.0, 0.0);
    Globals::light1->set_diffuse(0.5, 0.5, 0.5, 1.0);
    Globals::light1->set_specular(0.0, 0.0, 0.0, 0.0);
    Globals::light1->enable();
}




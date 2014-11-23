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

    // Generate light source:
    //glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
  
    // Install callback functions:
    glutDisplayFunc(Window::display_callback);
    glutReshapeFunc(Window::reshape_callback);
    glutIdleFunc(Window::idle_callback);
    
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

        case 'p':
            Globals::pause = !Globals::pause;
			break;

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


        case 'a':
			break;

        case 'l':
            Globals::light1->disable();
            Globals::light2->disable();
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
            if(Globals::light2->enabled()) {
                Globals::light2->disable();
            }
            else {
                Globals::light2->enable();
            }
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
            //Globals::focus = Globals::bunny;
            break;

        case GLUT_KEY_F2:
            //Globals::focus = Globals::dragon;

            break;

        case GLUT_KEY_F3:
            //Globals::focus = Globals::bear;

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
    Globals::bunny = new Model("obj/bunny.obj");
    //Globals::dragon = new Model("obj/dragon.obj");
    //Globals::bear = new Model("obj/bear.obj");

    Globals::focus = Globals::bunny;
    //Globals::focus = Globals::dragon;
    //Globals::focus = Globals::bear;

    float no_mat[] = {0.0, 0.0, 0.0, 1.0};
    float mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
    float mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
    float mat_diffuse[] = {0.1, 0.5, 0.8, 1.0};
    float mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    float no_shininess[] = {0.0};
    float low_shininess[] = {5.0};
    float high_shininess[] = {100.0};
    float mat_emission[] = {0.3, 0.2, 0.2, 0.0};

    Material material1;
    material1.set_ambient(no_mat);
    material1.set_diffuse(mat_diffuse);
    material1.set_specular(no_mat);
    material1.set_shininess(no_shininess);
    material1.set_emission(no_mat);

    Material material2;
    material2.set_ambient(no_mat);
    material2.set_diffuse(mat_diffuse);
    material2.set_specular(mat_specular);
    material2.set_shininess(low_shininess);
    material2.set_emission(no_mat);

    Material material3;
    material3.set_ambient(no_mat);
    material3.set_diffuse(mat_diffuse);
    material3.set_specular(mat_specular);
    material3.set_shininess(high_shininess);
    material3.set_emission(no_mat);
    
    //Globals::bunny->set_material(material1);
    //Globals::bunny->set_material(material2);
    Globals::bunny->set_material(material3);

    Globals::light1 = new Light(1);
    Globals::light1->set_ambient(0.0, 0.0, 0.0, 0.0);
    Globals::light1->set_diffuse(1.2, 1.2, 1.2, 1.0);
    Globals::light1->set_specular(0.0, 0.0, 0.0, 0.0);

    Globals::light2 = new SpotLight(2);
    Globals::light2->set_position(0.0, 0.0, 10.0, 1.0);
    Globals::light2->set_direction(0.0, 0.0, -1.0);

    Globals::light2->set_ambient(0.1, 0.1, 0.1, 1.0);
    Globals::light2->set_diffuse(1.0, 1.0, 0.0, 1.0);
    Globals::light2->set_specular(0.0, 0.0, 0.0, 1.0);

    Globals::light2->set_cutoff(10.0);
    Globals::light2->set_exponent(45.0);

    //Globals::light2->enable();
}




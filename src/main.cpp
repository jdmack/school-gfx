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

#define kPi 3.14159265359

// TODO:
// - Camera has to be transposed and inverted to work right, fix this


    Material material1;

    Material material2;

    Material material3;

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
            Globals::light1->disable();
            Globals::light2->disable();
			break;

        case 'l':
            Globals::mouse_light = !Globals::mouse_light;
			break;

        case '1':
            /*
            if(Globals::light1->enabled()) {
                Globals::light1->disable();
                //Globals::focus->shader()->set_active(false);
            }
            else {
                Globals::light1->enable();
                //Globals::focus->shader()->set_active(true);
            }
            */
            Globals::focus->set_material(material1);
            break;

        case '2':
            /*
            if(Globals::light2->enabled()) {
                Globals::light2->disable();
            }
            else {
                Globals::light2->enable();
            }
            */
            Globals::focus->set_material(material2);
            break;

        case '3':
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
            Globals::focus = Globals::bunny;
            break;

        case GLUT_KEY_F2:
            Globals::focus = Globals::dragon;

            break;

        case GLUT_KEY_F3:
            Globals::focus = Globals::bear;

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

    // setup shaders
    Shader * bunny_shader = new Shader("shader/spot_light.vert", "shader/spot_light.frag", true);
    bunny_shader->set_active(false);
    //Shader * bunny_shader = new Shader("shader/minimal.vert", "shader/minimal.frag", true);
    Globals::bunny->set_shader(bunny_shader);
    //Globals::dragon->set_shader(bunny_shader);
    //Globals::bear->set_shader(bunny_shader);

    float none[] = {0.0, 0.0, 0.0, 1.0};

    //float red[] = {0.8, 0.1, 0.1, 1.0};
    //float green[] = {0.1, 0.2, 0.1, 1.0};
    //float blue[] = {0.1, 0.1, 0.2, 1.0};

    float light[] = {0.1, 0.1, 0.1, 1.0};
    float medium[] = {0.3, 0.3, 0.3, 1.0};
    float heavy[] = {0.5, 0.5, 0.5, 1.0};
    //float full[] = {1.0, 1.0, 1.0, 1.0};

    float no_shininess[] = {0.0};
    float low_shininess[] = {5.0};
    float high_shininess[] = {100.0};

    material1.set_ambient(none);
    material1.set_diffuse(light);
    material1.set_specular(light);
    material1.set_shininess(no_shininess);
    //material1.set_emission(red);

    material2.set_ambient(none);
    material2.set_diffuse(medium);
    material2.set_specular(medium);
    material2.set_shininess(low_shininess);
    //material2.set_emission(green);

    //material3.set_ambient(blue);
    material3.set_diffuse(medium);
    material3.set_specular(heavy);
    material3.set_shininess(high_shininess);
    //material3.set_emission(blue);

    
    Globals::bunny->set_material(material1);
    //Globals::dragon->set_material(material2);
    //Globals::bear->set_material(material3);

    Globals::light2 = new Light(1);
    Globals::light2->set_position(-3.0, 3.0, 0.0, 1.0);
    //Globals::light2->set_ambient(1.0, 1.0, 1.0, 1.0);
    Globals::light2->set_ambient(0.0, 0.0, 0.0, 1.0);
    Globals::light2->set_diffuse(0.5, 0.5, 0.5, 1.0);
    //Globals::light2->set_diffuse(0.0, 0.0, 0.0, 1.0);
    Globals::light2->set_specular(0.5, 0.5, 0.5, 1.0);

    Globals::light1 = new SpotLight(0);
    Globals::light1->set_position(0.0, 0.0, 10.0, 1.0);
    Globals::light1->set_direction(0.0, 0.0, -1.0);

    Globals::light1->set_ambient(0.1, 0.1, 0.1, 1.0);
    Globals::light1->set_diffuse(1.0, 1.0, 0.0, 1.0);
    Globals::light1->set_specular(0.0, 0.0, 0.0, 1.0);

    Globals::light1->set_cutoff(10.0);
    Globals::light1->set_exponent(0.0);

    Globals::light2->enable();
}




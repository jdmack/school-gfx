#include "glee.h"
#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#include "window.h"
#include "matrix4.h"
#include "globals.h"
#include "timer.h"
#include "model.h"
#include "trackball.h"
#include "light.h"
#include "vector4.h"
#include "texture.h"
//#include "skybox.h"

#include <GL/glut.h>

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

    
    GWindow::width = glutGet(GLUT_SCREEN_WIDTH) - 10;
    GWindow::height = glutGet(GLUT_SCREEN_HEIGHT) - 70;
    glutInitWindowSize(GWindow::width, GWindow::height);      // set initial window size
    glutCreateWindow("CSE167 Final Project");    	        // open window and set window title

    // Display OpenGL Version
    std::cerr << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

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
    
    //glEnable(GL_CULL_FACE);                        // disable backface culling to render both sides of polygons
    //glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);             	        // set shading to smooth
    glMatrixMode(GL_PROJECTION); 
  
    // Generate material properties:
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // Enable Lighting
    // Generate light source:
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  
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

        case 'J':
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
			break;


        case 'e':
			break;

        case 'l':
			break;

        case '1':
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
    
    // Setup floor
    Globals::floor = new Floor();

    // Setup swords
    Model * sword1 = new Model("obj/sword1.obj");
    
    sword1->matrix_obj().rotate_y(-90);
    sword1->matrix_obj().rotate_x(90);



    Texture * texture = new Texture("texture/sword1.ppm");
    sword1->set_texture(texture);

    


    // Setup skybox
    //Globals::skybox = new Skybox(20);

    // Setup light
    Globals::light1 = new Light(0);
    Globals::light1->set_position(0.0, 10.0, 0.0, 1.0);
    Globals::light1->set_ambient(0.0, 0.0, 0.0, 1.0);
    //Globals::light1->set_diffuse(0.5, 0.5, 0.5, 1.0);
    Globals::light1->set_diffuse(0.8, 0.8, 0.8, 1.0);
    Globals::light1->set_specular(0.4, 0.4, 0.4, 1.0);
    Globals::light1->enable();

    // Setup material
    //float none[] = {0.0, 0.0, 0.0, 1.0};

    //float red[] = {0.8, 0.1, 0.1, 1.0};
    //float green[] = {0.1, 0.2, 0.1, 1.0};
    //float blue[] = {0.1, 0.1, 0.2, 1.0};

    /*
    float light[] = {0.1, 0.1, 0.1, 1.0};
    float medium[] = {0.3, 0.3, 0.3, 1.0};
    float heavy[] = {0.5, 0.5, 0.5, 1.0};
    float full[] = {1.0, 1.0, 1.0, 1.0};

    float no_shininess[] = {0.0};
    float low_shininess[] = {50.0};
    float high_shininess[] = {100.0};

    Material material1;
    material1.set_ambient(none);
    material1.set_diffuse(light);
    material1.set_specular(light);
    material1.set_shininess(low_shininess);
    //material1.set_emission(red);
    */


    // Set focus
    Globals::focus = static_cast<Object *>(sword1);

    //Globals::focus = new Model("obj/bunny.obj");

}




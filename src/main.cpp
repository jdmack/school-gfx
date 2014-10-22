#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glut.h>

#include "window.h"
#include "object.h"
#include "cube.h"
#include "matrix4.h"
#include "globals.h"
#include "timer.h"



void keyboard_callback(unsigned char key, int x, int y);
void keyboard_special_callback(int key, int x, int y);

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

    Globals::focus = static_cast<Object *>(&Globals::cube);
    
    glutMainLoop();
    return 0;
}

//----------------------------------------------------------------------------
// 
void keyboard_callback(unsigned char key, int x, int y)
{
    switch (key) {
        // 't: toggle the direction of the spin between clockwise and counterclockwise. (5 points)
        case 't':
            Globals::focus->toggle_spin();
            break;

        // 'x'/'X': move cube left/right by a small amount. (5 points)
        case 'x':
            Globals::focus->matrix_o2w().translate(-1.0, 0.0, 0.0);
			Globals::focus->position().x()--;
            break;
        case 'X':
            Globals::focus->matrix_o2w().translate(1.0, 0.0, 0.0);
			Globals::focus->position().x()++;
            break;

        // 'y'/'Y': move cube down/up by a small amount. (5 points)
        case 'y':
            Globals::focus->matrix_o2w().translate(0.0, -1.0, 0.0);
			Globals::focus->position().y()--;
            break;
        case 'Y':
            Globals::focus->matrix_o2w().translate(0.0, 1.0, 0.0);
			Globals::focus->position().y()++;
            break;

        // 'z'/'Z': move cube into/out of the screen by a small amount. (5 points)
        case 'z':
            Globals::focus->matrix_o2w().translate(0.0, 0.0, -1.0);
			Globals::focus->position().z()--;
            break;
        case 'Z':
            Globals::focus->matrix_o2w().translate(0.0, 0.0, 1.0);
			Globals::focus->position().z()++;
            break;
        
        // 'r': reset cube position, orientation, size and color. (5 points)
        case 'r':
            Globals::focus->reset();

            break;

        // 'b': Switch between ball and cube
        case 'b':
            if(Globals::focus == static_cast<Object *>(&Globals::cube)) {
                Globals::focus = static_cast<Object *>(&Globals::ball);
            }
            else {
                Globals::focus = static_cast<Object *>(&Globals::cube);
            }
            break;


			//'o' / 'O': orbit cube about the OpenGL window's z axis by a small number of degrees (e.g., 10) per key press, 
			// counterclockwise ('o') or clockwise ('O'). The z axis crosses the screen in the center of the OpenGL window. 
			// This rotation should not affect the spin other than that it will rotate the spin axis with the cube. (10 points)
        case 'o':
			Globals::focus->matrix_o2w().rotate_z(-5);
			break;
        case 'O':
			Globals::focus->matrix_o2w().rotate_z(5);
			break;

        // 's'/'S': scale cube down/up (about its center, not the center of the screen). To scale up means to
        // make it bigger (5 points)
        case 's':
			Globals::focus->matrix_obj().scale(.90, .90, .90);
			break;
        case 'S':
			Globals::focus->matrix_obj().scale(1.10, 1.10, 1.10);
			break;
		case 'f':
			Globals::focus->matrix_o2w().identity();
			Globals::focus->matrix_obj().identity();
			//light0_matrix.identity();
			//light1_matrix.identity();
			//light2_matrix.identity();

			//if (!cube_flag) {
			//    focus->scale_matrix().scale(scale_number, scale_number, scale_number);
			//}
			break;

		case 'm':       // Model freeze toggle
			//if (freeze_toggle) {
			//    freeze_toggle = false;
			//}
			//else {
			//    freeze_toggle = true;
			//}
			break;

		case 27:
			exit(0);
			break;
    }

    // With every key press, display the new cube position with your 
    // Vector3 print method in the text window. (5 points)
    //std::cout << "Position: ";
    Vector4 pos;
    Globals::focus->matrix().multiply(pos).print();
    //pos.print();
}

void keyboard_special_callback(int key, int x, int y)
{
    switch (key) {
        // F1 - Display Cube
        case GLUT_KEY_F1:
            std::cout << "Display Cube\n";

            Globals::focus = static_cast<Object *>(&Globals::cube);

            break;

        // F2 - Display House View 1
        case GLUT_KEY_F2:
            std::cout << "Display House View 1\n";

            Globals::focus = static_cast<Object *>(&Globals::house);

            break;

        // F3 - Display House View 2
        case GLUT_KEY_F3:
            std::cout << "Displaying House View 2\n";

            Globals::focus = static_cast<Object *>(&Globals::house);

            break;

        // F3 - Display Bunny
        /*
        case GLUT_KEY_F3:
            std::cout << "\nDisplaying Bunny\n----------------------\n";

            glutDisplayFunc(display_object);
            glutIdleFunc(idle_callback2);

            scale_number = scale_bunny;
            current_object = kBunny;

            object = object_bunny;
            focus->reset();
            calculate_stuff();

            break;
        */

        // F4 - Display Sandal
        /*
        case GLUT_KEY_F4:
            std::cout << "\nDisplaying Sandal\n----------------------\n";

            glutDisplayFunc(display_object);
            glutIdleFunc(idle_callback2);

            scale_number = scale_sandal;
            current_object = kSandal;

            object = object_sandal;
            focus->reset();
            calculate_stuff();

            break;
        */

        // F5
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

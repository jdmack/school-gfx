#include <iostream>

#include <GL/glut.h>

#include "window.h"
#include "matrix4.h"
#include "globals.h"
#include "timer.h"

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
Timer Window::timer_ = Timer();

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idle_callback()
{
    //Globals::root->update(timer_.get_ticks());
    Globals::root->update(15);
    Globals::root->update_bound(Globals::identity_matrix);
    timer_.start();
    display_callback();         // call display routine to show the object
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshape_callback(int w, int h)
{
    std::cerr << "Window::reshape_callback called" << std::endl;
    width = w;
    height = h;
    glViewport(0, 0, w, h);  // set new viewport size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
    glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
    glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
    glEnable(GL_LIGHTING);

    // Draw current object
    Matrix4 matrix = Matrix4();
    matrix.identity();

    Globals::root->draw(matrix);

    glFlush();  
    glutSwapBuffers();
}

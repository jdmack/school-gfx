#include <iostream>

#include <GL/gl.h>
#include <GL/glut.h>

#include "window.h"
#include "object.h"
#include "matrix4.h"
#include "globals.h"
#include "struct.h"
#include "timer.h"

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

float * Window::pixels = new float[Window::width * Window::height * 3];

Timer Window::timer_ = Timer();

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idle_callback()
{
    Globals::focus->update(timer_.get_ticks());
    timer_.start();
    display_callback();         // call display routine to show the object
}

// Called whenever the window size changes
void Window::reshape_callback(int new_width, int new_height)
{
    width  = new_width;
    height = new_height;

    delete[] pixels;

    pixels = new float[width * height * 3];

    display_callback();
}

void Window::display_callback()
{
    clear_buffer();
    rasterize();

    // glDrawPixels writes a block of pixels to the framebuffer
    glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

    glutSwapBuffers();
}

/*
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
    Globals::focus->display(Globals::camera);

    glFlush();  
    glutSwapBuffers();
}
*/

void Window::rasterize()
{
    // Put your main rasterization loop here
    // It should go over the point model and call drawPoint for every point in it

}

// Draw a point into the frame buffer
void Window::draw_point(int x, int y, float r, float g, float b)
{
    int offset = y*width*3 + x*3;

    pixels[offset]   = r;
    pixels[offset+1] = g;
    pixels[offset+2] = b;
}

// Clear frame buffer
void Window::clear_buffer()
{
    Color clear_color = {0.0, 0.0, 0.0};   // clear color: black
    for(int i = 0; i < width * height; ++i) {
        pixels[i * 3]     = clear_color.r;
        pixels[i * 3 + 1] = clear_color.g;
        pixels[i * 3 + 2] = clear_color.b;
    }
}


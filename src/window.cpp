#ifdef _WIN32
    #include <windows.h>
#endif

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
    std::cerr << "Window::reshape_callback called - width: " << new_width << ", height: " << new_height << std::endl;

    width  = new_width;
    height = new_height;


    delete[] pixels;

    pixels = new float[width * height * 3];

    int v_width = width;
    int v_height = height;

    if(width != height) {

        if(width > height) {
            v_width = height;
        }
        else if(height > width) {
            v_height = width;
        }
    }

    set_viewport(0, 0, v_width, v_height);

    //std::cerr << "Viewport: " << std::endl;;
    //Globals::viewport.print();

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
    // It should go over the point model and call draw_point for every point in it

    std::vector<Vector3> points = Globals::focus->points();


    //std::cerr << "points: " << points.size() << std::endl;

    Vector4 point;
    for(std::vector<Vector3>::iterator it = points.begin(); it != points.end(); ++it) {
        point = Vector4((*it).x(), (*it).y(), (*it).z());

        Globals::focus->matrix().identity();
        Globals::focus->matrix().set(Globals::focus->matrix().multiply(Globals::focus->matrix_obj()));
        Globals::focus->matrix().set(Globals::focus->matrix().multiply(Globals::focus->matrix_o2w()));

        point = Globals::focus->matrix().multiply(point);
        point = Globals::camera.c().multiply(point);
        point = Globals::perspective.multiply(point);
        point.dehomogenize();
        point = Globals::viewport.multiply(point);

        if((point.x() < Window::width) && (point.y() < Window::height)) {
            draw_point(point.x(), point.y(), 255, 255, 255);
        }
    }
}

// Draw a point into the frame buffer
void Window::draw_point(int x, int y, float r, float g, float b)
{
    //std::cerr << "(" << x << ", " << y << ")" << std::endl;

    if((x < 0) || (y < 0)) return;

    if(width != height) {
        if(width > height) {
            x += ((width - height) / 2);
        }
        else if(height > width) {
            y += ((height - width) / 2);
        }
    }

    int offset = y * width * 3 + x * 3;

    pixels[offset]     = r;
    pixels[offset + 1] = g;
    pixels[offset + 2] = b;
}

// Clear frame buffer
void Window::clear_buffer()
{
    Color clear_color = {0.0, 0.0, 0.0};   // clear color: black
    //Color clear_color = {255.0, 255.0, 255.0};   // clear color: black
    for(int i = 0; i < width * height; ++i) {
        pixels[i * 3]     = clear_color.r;
        pixels[i * 3 + 1] = clear_color.g;
        pixels[i * 3 + 2] = clear_color.b;
    }
}

void Window::set_viewport(int x, int y, int width, int height)
{
    int x0 = x;
    int y0 = y;
    int x1 = width;
    int y1 = height;

    Globals::viewport = Matrix4(
        (x1 - x0) / 2, 0, 0, (x0 + x1) / 2,
        0, (y1 - y0) / 2, 0, (y0 + y1) / 2,
        0, 0, 0.5, 0.5,
        0, 0, 0, 1
    );

    Globals::viewport.transpose();
}



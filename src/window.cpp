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
#include "color.h"
#include "timer.h"

#define PI 3.14159265
#define Z_DEFAULT 1

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

float * Window::pixels = new float[Window::width * Window::height * 3];
float * Window::zbuffer = new float[Window::width * Window::height];

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
    delete[] zbuffer;

    pixels = new float[width * height * 3];
    zbuffer = new float[width * height];

    set_perspective(width, height);
    set_viewport(0, 0, width, height);

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
    std::vector<Vector3> normals = Globals::focus->normals();

    Vector3 light_pos = Vector3(-50, -50, -50);
    Color material_color = Color(1.0, 1.0, 1.0);
    Color light_color = Color(0.5, 0.5, 0.5);
    light_color = light_color * 1;

    //std::cerr << "points: " << points.size() << std::endl;

    Vector3 point3;
    Vector4 point4;
    Vector3 normal3;
    Vector4 normal4;

    for(unsigned int i = 0; i < points.size(); i++) {
        point4 = Vector4(points[i].x(), points[i].y(), points[i].z());
        normal4 = Vector4(normals[i].x(), normals[i].y(), normals[i].z(), 0);

        Globals::focus->matrix().identity();
        Globals::focus->matrix().set(Globals::focus->matrix().multiply(Globals::focus->matrix_obj()));
        Globals::focus->matrix().set(Globals::focus->matrix().multiply(Globals::focus->matrix_o2w()));

        point4 = Globals::focus->matrix().multiply(point4);
        point4 = Globals::camera.c().multiply(point4);
        point4 = Globals::perspective.multiply(point4);
        point4.dehomogenize();
        point4 = Globals::viewport.multiply(point4);

        normal4 = Globals::focus->matrix_obj().multiply(normal4);
        normal4 = Globals::focus->matrix_o2w().multiply(normal4);

        point3 = Vector3(point4.x(), point4.y(), point4.z());
        normal3 = Vector3(normal4.x(), normal4.y(), normal4.z());
        normal3.normalize();

        if((point3.x() < Window::width) && (point3.y() < Window::height)) {
            Color color = material_color;
            if(Globals::light) {

                // Light direction
                Vector3 light_dir = light_pos - point3;
                light_dir.normalize();

                // Distance from light_pos to point
                double distance = light_pos.distance_from(point3);

                // Light color at distance
                Color light_color_distance = light_color;// / (distance * distance);


                double dot_product = light_dir.dot_product(normal3);

                Color reflected_color = light_color_distance * material_color;
                reflected_color = reflected_color / PI;
                reflected_color = reflected_color * dot_product;

                color = reflected_color;

                //std::cout << "Color: " << reflected_color.str() << std::endl;
            }

            draw_point(point3.x(), point3.y(), color.r(), color.g(), color.b());
        }
    }
}

// Draw a point into the frame buffer
void Window::draw_point(int x, int y, float r, float g, float b)
{
    //std::cerr << "(" << x << ", " << y << ")" << std::endl;

    if((x < 0) || (y < 0)) return;

    int offset = y * width * 3 + x * 3;

    pixels[offset]     = r;
    pixels[offset + 1] = g;
    pixels[offset + 2] = b;
}

// Clear frame buffer
void Window::clear_buffer()
{
    Color clear_color = Color(0.0, 0.0, 0.0);   // clear color: black
    //Color clear_color = {255.0, 255.0, 255.0};   // clear color: black
    for(int i = 0; i < width * height; ++i) {
        pixels[i * 3]     = clear_color.r();
        pixels[i * 3 + 1] = clear_color.g();
        pixels[i * 3 + 2] = clear_color.b();
        zbuffer[i] = Z_DEFAULT;
    }
}

void Window::set_perspective(double width, double height)
{
    double aspect = width / height;
    std::cerr << "Aspect: " << aspect << std::endl;

    double fov    = 60;

    double z_near = 1.0;
    double z_far  = 1000.0;

    fov = fov * PI / 180.0;

    Globals::perspective = Matrix4(
        1 / (aspect * std::tan(fov / 2)), 0, 0, 0,
        0, 1/(std::tan(fov/2)), 0, 0,
        0, 0, (z_near + z_far) / (z_near - z_far), (2 * z_near * z_far) / (z_near - z_far),
        0, 0, -1, 0
    );
    Globals::perspective.transpose();
    std::cerr << "Projection: " << std::endl;;
    Globals::perspective.print();

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
    std::cerr << "Viewport: " << std::endl;;
    Globals::viewport.print();
}



#ifndef CSE167_WINDOW_H_
#define CSE167_WINDOW_H_

#include "timer.h"

class Window	  // OpenGL output window related routines
{
    public:
        static int width, height; 	            // window size
        static float * pixels;

        static Timer timer_;

        static void idle_callback();
        static void reshape_callback(int, int);
        static void display_callback();

        static void rasterize();
        static void draw_point(int x, int y, float r, float g, float b);
        static void clear_buffer();

        static void set_viewport(int x, int y, int width, int height);

};

#endif


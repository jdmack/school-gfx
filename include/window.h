#ifndef CSE167_WINDOW_H_
#define CSE167_WINDOW_H_

#include "timer.h"

class GWindow	  // OpenGL output window related routines
{
    public:
        static int width, height; 	            // window size
        static Timer timer_;

        static void idle_callback(void);
        static void reshape_callback(int, int);
        static void display_callback(void);


};

#endif


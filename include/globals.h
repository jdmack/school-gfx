#ifndef CSE167_GLOBALS_H_
#define CSE167_GLOBALS_H_

#include "camera.h"
#include "object.h"
#include "ball.h"
#include "cube.h"
#include "house.h"
#include "point_cloud.h"
#include "matrix4.h"


namespace Globals
{
    extern Camera camera;
    extern Object * focus;
    //extern Ball ball;
    extern Cube cube;
    extern House house;
    extern PointCloud bunny;
    extern PointCloud dragon;
    extern Matrix4 perspective;
    extern Matrix4 viewport;
    extern bool light;
    extern bool zbuffer;
    extern bool psize;
};

#endif


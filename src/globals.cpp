#include "globals.h"
#include "camera.h"
#include "object.h"
#include "ball.h"
#include "cube.h"
#include "house.h"
#include "point_cloud.h"

namespace Globals
{
    Camera camera = Camera();
    Object * focus;
    Ball ball = Ball();
    Cube cube = Cube();
    House house = House();
    //PointCloud bunny = PointCloud("xyz/bunny.xyz");
    //PointCloud dragon = PointCloud("xyz/dragon.xyz");
    PointCloud bunny = PointCloud();
    PointCloud dragon = PointCloud();
};

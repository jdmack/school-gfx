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
    Matrix4 perspective = Matrix4();
    Matrix4 viewport = Matrix4();

    //Matrix4 viewport = Matrix4(
    //    1, 0, 0, 0,
    //    0, 1, 0, 0,
    //    0, 0, 0.5, 0.5,
    //    0, 0, 0, 1
    //);
    //Matrix4 viewport = Matrix4(
    //    (1 - (-1)) / 2, 0, 0, (-1 + 1) / 2,
    //    0, (1 - (-1)) / 2, 0, (-1 + 1) / 2,
    //    0, 0, 1/2, 1/2,
    //    0, 0, 0, 1
    //);
};

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
    //Ball ball = Ball();
    Cube cube = Cube();
    House house = House();
    PointCloud bunny = PointCloud();
    PointCloud dragon = PointCloud();
    Matrix4 perspective = Matrix4();
    Matrix4 viewport = Matrix4();
    bool light = true;
    bool zbuffer = false;
    bool psize = false;
};

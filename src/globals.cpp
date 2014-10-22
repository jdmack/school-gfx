#include "globals.h"
#include "camera.h"
#include "object.h"
#include "ball.h"
#include "cube.h"
#include "house.h"

namespace Globals
{
    Camera camera = Camera();
    Object * focus;
    Ball ball = Ball();
    Cube cube = Cube();
    House house = House();
};

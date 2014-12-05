#include "globals.h"
#include "camera.h"
#include "model.h"
#include "light.h"
#include "spot_light.h"

namespace Globals
{
    Camera camera = Camera();
    bool flag = false;
    bool pause = false;
    Matrix4 identity_matrix;
    bool mouse_light = false;

    Model * bunny;
    Model * dragon;
    Model * bear;
    Model * focus;
    Light * light2;
    SpotLight * light1;
};

#ifndef CSE167_GLOBALS_H_
#define CSE167_GLOBALS_H_

#include "model.h"
#include "camera.h"
#include "light.h"
#include "spot_light.h"

namespace Globals
{
    extern Camera camera;
    extern bool flag;
    extern bool pause;
    extern Model * bunny;
    extern Model * dragon;
    extern Model * bear;
    extern Model * focus;
    extern bool mouse_light;
    
    extern Light * light2;
    extern SpotLight * light1;
    extern Matrix4 identity_matrix;

};

#endif


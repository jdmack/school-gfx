#ifndef CSE167_GLOBALS_H_
#define CSE167_GLOBALS_H_

#include "camera.h"
#include "model.h"
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
    
    extern Light * light1;
    extern SpotLight * light2;
    extern Matrix4 identity_matrix;

};

#endif


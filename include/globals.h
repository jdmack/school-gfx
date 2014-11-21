#ifndef CSE167_GLOBALS_H_
#define CSE167_GLOBALS_H_

#include "camera.h"
#include "frustum.h"
#include "model.h"

namespace Globals
{
    extern Camera camera;
    extern bool flag;
    extern bool pause;
    extern Model * bunny;
    extern Model * dragon;
    extern Model * bear;
    extern Model * focus;
    
    extern Matrix4 identity_matrix;

};

#endif


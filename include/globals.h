#ifndef CSE167_GLOBALS_H_
#define CSE167_GLOBALS_H_

#include "object.h"
#include "camera.h"
#include "light.h"
#include "shader.h"
#include "skybox.h"

namespace Globals
{
    extern Camera camera;
    extern bool flag;
    extern bool pause;
    extern Matrix4 identity_matrix;

    extern Object * focus;
    extern Light * light1;
    extern Skybox * skybox;

};

#endif


#ifndef CSE167_GLOBALS_H_
#define CSE167_GLOBALS_H_

#include "model.h"
#include "camera.h"
#include "light.h"
#include "bezier_patch.h"
#include "skybox.h"

namespace Globals
{
    extern Camera camera;
    extern bool flag;
    extern bool pause;
    extern Matrix4 identity_matrix;

    extern Model * focus;
    extern Light * light1;
    extern BezierPatch * bezier_patch;
    extern Skybox * skybox;

};

#endif


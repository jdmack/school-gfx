#include "globals.h"
#include "camera.h"
#include "model.h"
#include "light.h"
#include "bezier_patch.h"
#include "skybox.h"

namespace Globals
{
    Camera camera = Camera();
    bool flag = false;
    bool pause = false;
    Matrix4 identity_matrix;

    Model * focus;
    Light * light1;
    BezierPatch * bezier_patch;
    Skybox * skybox;
};

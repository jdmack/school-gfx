#include "globals.h"
#include "camera.h"

namespace Globals
{
    Camera camera = Camera();
    MatrixTransform * root;// = new Group();
    bool flag = false;
    bool show_bound = false;
    bool pause = false;
    bool culling = false;
    Frustum frustum;
    Matrix4 identity_matrix;
};

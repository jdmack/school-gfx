#ifndef CSE167_GLOBALS_H_
#define CSE167_GLOBALS_H_

#include "camera.h"
#include "matrix_transform.h"
#include "frustum.h"


namespace Globals
{
    extern Camera camera;
    extern MatrixTransform * root;
    extern bool flag;
    extern bool show_bound;
    extern bool pause;
    extern bool culling;
    extern Frustum frustum;
    
    extern Matrix4 identity_matrix;

};

#endif


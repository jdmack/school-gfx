#ifndef CSE167_TRACKBALL_H_
#define CSE167_TRACKBALL_H_

#include "vector3.h"
#include "matrix4.h"

const double kRotateScale = 180.0;

enum MouseMovement {
    ROTATE,
    ZOOM,
    NONE
};

class Trackball
{

    public:
        static MouseMovement movement;
        static Vector3 last_point;
        static Matrix4 rotation;
        static Matrix4 scaling;

        static void mouse_move(int x, int y);
        static void mouse_func(int button, int state, int x, int y);
        static Vector3 trackball_mapping(int x, int y);

};

#endif

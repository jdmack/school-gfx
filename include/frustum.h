#ifndef CSE167_FRUSTRUM_H_
#define CSE167_FRUSTRUM_H_

#include "vector3.h"
#include "plane.h"
#include "aa_box.h"

enum {
    TOP = 0,
    BOTTOM,
    LEFT,
    RIGHT,
    NEARP,
    FARP
};
static enum { OUTSIDE, INTERSECT, INSIDE };


class Frustum 
{
    private:

        enum {
            TOP = 0, BOTTOM, LEFT,
            RIGHT, NEARP, FARP
        };

    public:

        Plane pl[6];
        Vector3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
        float nearD, farD, ratio, angle, tang;
        float nw, nh, fw, fh;

        Frustum();
        ~Frustum();

        void setCamInternals(float angle, float ratio, float nearD, float farD);
        void setCamDef(Vector3 &p, Vector3 &l, Vector3 &u);
        bool pointInFrustum(Vector3 &p);
        bool sphereInFrustum(Vector3 &p, float radius);
};

#endif
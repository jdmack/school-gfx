#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "frustum.h"
#include "globals.h"


#define ANG2RAD 3.14159265358979323846/180.0

Frustum::Frustum()
{

}

Frustum::~Frustum()
{

}

void Frustum::setCamInternals(float angle, float ratio, float nearD, float farD) {

    this->ratio = ratio;
    this->angle = angle;
    this->nearD = nearD;
    this->farD = farD;

    tang = (float)tan(angle* ANG2RAD * 0.5);
    nh = nearD * tang;
    nw = nh * ratio;
    fh = farD  * tang;
    fw = fh * ratio;

}


void Frustum::setCamDef(Vector3 p, Vector3 l, Vector3 u) {

    Vector3 dir, nc, fc, X, Y, Z;

    Z = p - l;
    Z.normalize();

    X = u.cross_product(Z);
    X.normalize();

    Y = Z.cross_product(X);

    nc = p - Z * nearD;
    fc = p - Z * farD;

    ntl = nc + Y * nh - X * nw;
    ntr = nc + Y * nh + X * nw;
    nbl = nc - Y * nh - X * nw;
    nbr = nc - Y * nh + X * nw;

    ftl = fc + Y * fh - X * fw;
    ftr = fc + Y * fh + X * fw;
    fbl = fc - Y * fh - X * fw;
    fbr = fc - Y * fh + X * fw;

    pl[TOP].set3Points(ntr, ntl, ftl);
    pl[BOTTOM].set3Points(nbl, nbr, fbr);
    pl[LEFT].set3Points(ntl, nbl, fbl);
    pl[RIGHT].set3Points(nbr, ntr, fbr);
    pl[NEARP].set3Points(ntl, ntr, nbr);
    pl[FARP].set3Points(ftr, ftl, fbl);
}


bool Frustum::pointInFrustum(Vector3 p) {

    int result = true;
    for(int i = 0; i < 6; i++) {

        if(pl[i].distance(p) < 0)
            return false;
    }
    return(result);

}


bool Frustum::sphereInFrustum(Vector3 p, float radius)
{
    
    if(!Globals::culling) return true;
    if(radius <= 0) return true;
    int result = true;
    float distance;

    for(int i = 0; i < 6; i++) {
        distance = pl[i].distance(p);
        if(distance < -radius)
            return false;
        else if(distance < radius)
            result = true;
    }
    return(result);

}

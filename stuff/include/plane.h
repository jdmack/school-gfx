#ifndef CSE167_PLANE_H_
#define CSE167_PLANE_H_

#include "vector3.h"

class Vector3;

class Plane  
{

    public:
        Vector3 normal,point;
        float d;

        Plane( Vector3 &v1,  Vector3 &v2,  Vector3 &v3);
        Plane(void);
        ~Plane();

        void set3Points( Vector3 &v1,  Vector3 &v2,  Vector3 &v3);
        void setNormalAndPoint(Vector3 &normal, Vector3 &point);
        void setCoefficients(float a, float b, float c, float d);
        float distance(Vector3 &p);

        void print();

};

#endif


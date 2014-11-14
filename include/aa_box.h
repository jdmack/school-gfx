#ifndef CSE167_AA_BOX_H_
#define CSE167_AA_BOX_H_

#include "vector3.h"

class AABox 
{
    public:

        Vector3 corner;
        float x,y,z;

        AABox(Vector3 &corner, float x, float y, float z);
        AABox(void);
        ~AABox();

        void AABox::setBox( Vector3 &corner, float x, float y, float z);

        // for use in frustum computations
        Vector3 AABox::getVertexP(Vector3 &normal);
        Vector3 AABox::getVertexN(Vector3 &normal);


};


#endif

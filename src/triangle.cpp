#include "triangle.h"

Triangle::Triangle()
{

}


Triangle::Triangle(Vector3 v1, Vector3 n1, Vector3 v2, Vector3 n2, Vector3 v3, Vector3 n3)
{
    vertex1_ = v1;
    vertex2_ = v2;
    vertex3_ = v3;
    normal1_ = n1;
    normal2_ = n2;
    normal3_ = n3;
}

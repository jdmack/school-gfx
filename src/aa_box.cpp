#include "aa_box.h"
#include "vector3.h"



AABox::AABox( Vector3 &corner,  float x, float y, float z)
{
	setBox(corner,x,y,z);
}

AABox::AABox(void)
{
	corner.x() = 0; corner.y() = 0; corner.z() = 0;

	x = 1.0f;
	y = 1.0f;
	z = 1.0f;
	
}

AABox::~AABox()
{

}

void AABox::setBox( Vector3 &corner,  float x, float y, float z)
{
	corner = Vector3(corner);

	if (x < 0.0) {
		x = -x;
		this->corner.x() -= x;
	}
	if (y < 0.0) {
		y = -y;
		this->corner.y() -= y;
	}
	if (z < 0.0) {
		z = -z;
		this->corner.z() -= z;
	}
	this->x = x;
	this->y = y;
	this->z = z;


}

Vector3 AABox::getVertexP(Vector3 &normal)
{

	Vector3 res = corner;

	if (normal.x() > 0)
		res.x() += x;

	if (normal.y() > 0)
		res.y() += y;

	if (normal.z() > 0)
		res.z() += z;

	return(res);
}

Vector3 AABox::getVertexN(Vector3 &normal)
{

	Vector3 res = corner;

	if(normal.x() < 0)
		res.x() += x;

	if(normal.y() < 0)
		res.y() += y;

	if(normal.z() < 0)
		res.z() += z;

	return(res);
}
	


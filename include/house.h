#ifndef CSE167_HOUSE_H_
#define CSE167_HOUSE_H_

#include "matrix4.h"
#include "vector4.h"
#include "object.h"
#include "camera.h"

class House : public Object
{
protected:

public:
    // constructors
    House();
       
    void display(Camera camera = Camera());
    void update(int ticks);
    void reset();
};

#endif


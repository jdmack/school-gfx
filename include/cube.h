#ifndef CSE167_CUBE_H_
#define CSE167_CUBE_H_

#include "matrix4.h"
#include "vector4.h"
#include "object.h"

class Cube : public Object
{
protected:
    
public:
    // constructors
    Cube();
       
    void display();
    void update(int ticks);
};

#endif


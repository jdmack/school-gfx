#ifndef CSE167_HOUSE_H_
#define CSE167_HOUSE_H_

#include "matrix4.h"
#include "vector4.h"
#include "object.h"

class House : public Object
{
protected:

public:
    // constructors
    House();
       
    void display();
    void update(int ticks);
    void reset();
};

#endif


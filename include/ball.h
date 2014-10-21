#ifndef CSE167_BALL_H_
#define CSE167_BALL_H_

#include "matrix4.h"
#include "vector4.h"
#include "object.h"

class Ball : public Object
{
protected:
    float radius_;
    Vector3 velocity_;
    Vector3 acceleration_;

public:
    // constructors
    Ball();
       
    void display();
    void update(int ticks);
    void reset();
};

#endif

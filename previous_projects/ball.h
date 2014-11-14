#ifndef CSE167_BALL_H_
#define CSE167_BALL_H_

#include "matrix4.h"
#include "vector4.h"
#include "object.h"
#include "camera.h"

class Ball : public Object
{
protected:
    float radius_;
    Vector3 velocity_;
    Vector3 acceleration_;

public:
    // constructors
    Ball();
       
    void display(Camera camera = Camera());
    void update(int ticks);
    void reset();
};

#endif


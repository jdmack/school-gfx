#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <GL/glut.h>

#include "ball.h"
#include "object.h"
#include "matrix4.h"
#include "vector2.h"

Ball::Ball() : Object()
{
    radius_ = 2;

    srand(time(NULL));
    int random_direction = rand() % 360;
    //std::cout << "direction: " << random_direction << std::endl;

    Vector2 v = Vector2(30.0, random_direction);

    velocity_ = Vector3(v.x_component(), v.y_component(), 0);
    //velocity_ = Vector3(30.0, 35.0, 0.0);
    acceleration_ = Vector3(0.0, -150.0, 0.0);

}


void Ball::display()
{
    glMatrixMode(GL_MODELVIEW);         // make sure we're in Objectview mode

    // Tell OpenGL what ObjectView matrix to use:

    matrix().identity();
    matrix().set(matrix().multiply(spin_matrix()));
    matrix().set(matrix().multiply(translate_matrix()));
    matrix().set(matrix().multiply(rotate_matrix()));
    matrix().set(matrix().multiply(scale_matrix()));
    glLoadMatrixd(matrix().pointer());

    // Draw sphere
    glutSolidSphere(radius_, 100.0f, 100.0f);
    
}

void Ball::update(int ticks)
{
    float border = 9;

    velocity_.x() += acceleration_.x() * (ticks / 1000.0);
    velocity_.y() += acceleration_.y() * (ticks / 1000.0);

    position_.x() += velocity_.x() * (ticks / 1000.0);
    position_.y() += velocity_.y() * (ticks / 1000.0);

    if(position_.x() >= border) {
        velocity_.x() *= -1;
        //velocity_.x() *= 0.90;
        velocity_.x() += 1.0;
        position_.x() = border;
    }
    else if(position_.x() <= -border) {
        velocity_.x() *= -1;
        //velocity_.x() *= 0.90;
        velocity_.x() -= 1.0;
        position_.x() = -border;
    }

    if(position_.y() >= border) {
        velocity_.y() *= -1;
        position_.y() = border;
    }
    else if(position_.y() <= -border) {
        velocity_.y() *= -1;
        position_.y() = -border;
    }

    if(velocity_.x() > 0) {
        velocity_.x() -= 0.2 * (ticks / 1000.0);
    }
    else {
        velocity_.x() += 0.2 * (ticks / 1000.0);
    }

    translate_matrix_.identity();
    translate_matrix_.translate(position_.x(), position_.y(), position_.z());
}

void Ball::reset()
{
    //movement_ = Vector3(1.0, 0.8, 0);

    int random_direction = rand() % 360;
    //std::cout << "direction: " << random_direction << std::endl;

    Vector2 v = Vector2(30.0, random_direction);
    velocity_ = Vector3(v.x_component(), v.y_component(), 0);

    Object::reset();
}

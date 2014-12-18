#include <iostream>
#include "object.h"
#include "camera.h"

#include "particle.h"

#include <GL/glut.h>

Particle::Particle()
{
    init();
}

Particle::Particle(Vector3 point) : Particle()
{
    init();
    position_ = point;
}

void Particle::init()
{
    // Random Position
    double p_x = (double)(rand() % 5) - 2.5;
    double p_y = (double)(rand() % 5) - 2.5;
    double p_z = (double)(rand() % 5) - 2.5;
    position_ = Vector3(p_x, p_y, p_z);
    position_ = Vector3(0,0,0);

    // Random Velocity
    double v_x = (double)(rand() % 5) - 2.5;
    double v_y = (double)(rand() % 5) - 2.5;
    double v_z = (double)(rand() % 5) - 2.5;
    velocity_ = Vector3(v_x, v_y, v_z);

    // Random Color
    double r = 1.0;
    double g = (double)(rand() % 100) / 100;
    double b = 0.0;
    color_ = Color(r, g, b);

    // Random Size
    size_ = (double)(rand() % 50) / 10.0;
    //size_ = 1;

    // Random lifetime
    lifetime_ = rand() % 5000;

    elapsed_time_ = 0;
    alive_ = true;

    /*
    std::cerr << "Creating Particle:" << std::endl;
    std::cerr << "\tposition: " << position_.str() << std::endl;
    std::cerr << "\tvelocity: " << velocity_.str() << std::endl;
    std::cerr << "\tcolor: " << color_.str() << std::endl;
    std::cerr << "\tsize: " << size_ << std::endl;
    std::cerr << "\tlifetime: " << lifetime_ << std::endl;
    */
}

void Particle::display(Camera camera)
{
    //std::cerr << "Displaying Particle: " << position_.str() << std::endl;
    if(alive_) {
        glPointSize(size_);
        glColor3f(color_.r(), color_.g(), color_.b());
        glBegin(GL_POINTS);
        glVertex3f(position_.x(), position_.y(), position_.z());
        glEnd();
    }
}

void Particle::update(int ticks)
{
    double dticks = (double) ticks / 100;
    elapsed_time_ += ticks;
    if(elapsed_time_ >= lifetime_) {
        alive_ = false;
    }

    if(alive_) {
        position_.x() += dticks * velocity_.x();
        position_.y() += dticks * velocity_.y();
        position_.z() += dticks * velocity_.z();
    }
}

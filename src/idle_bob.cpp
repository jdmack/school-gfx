#include <iostream>
#include "idle_bob.h"
#include "sword.h"

IdleBob::IdleBob() : Animation()
{
    height_velocity_ = rand() % 50 / (double)100;
    current_height_ = 0;
    max_height_ = 1;
    direction_ = rand() % 2;
    if(direction_ == 1) direction_ = -1;
    else direction_ = 1;

    std::cerr << "height_velocity: " << height_velocity_ << std::endl;
}

IdleBob::IdleBob(Sword * sword) : IdleBob()
{
    sword_ = sword;
}

bool IdleBob::update(int ticks)
{
    if(stop_) {
        if((current_height_ <= 0.1) && (current_height_ >= -0.1)) {
            current_height_ += -current_height_;
            sword_->matrix_o2w().translate(0, -current_height_, 0);
            return true; 
        }

    }

    if(direction_ < 0) {
        if(current_height_ <= -max_height_) {
            direction_ *= -1;
        }
    }
    else if(direction_ > 0) {
        if(current_height_ >= max_height_) {
            direction_ *= -1;
        }
    }

    double movement = direction_ * height_velocity_ * ticks / 100;
    current_height_ += movement;

    //std::cerr << "Bobbing: " << movement << std::endl;

    sword_->matrix_o2w().translate(0, movement, 0);

    return false;
}

#include <iostream>
#include "swing.h"
#include "sword.h"
#include "globals.h"
#include "particle_effect.h"

Swing::Swing() : Animation()
{
    //height_velocity_ = rand() % 50 / (double)100;

    x_pos_ = 0;
    y_pos_ = 0;
    z_pos_ = 0;

    x_rotate_ = 0;
    y_rotate_ = 0;
    z_rotate_ = 0;
    stage_ = 1;

    //std::cerr << "height_velocity: " << height_velocity_ << std::endl;
}

Swing::Swing(Sword * sword) : Swing()
{
    sword_ = sword;
}

bool Swing::update(int ticks)
{
    if(stop_) {
        /*
        if((current_height_ <= 0.1) && (current_height_ >= -0.1)) {
            current_height_ += -current_height_;
            sword_->matrix_o2w().translate(0, -current_height_, 0);
            return true; 
        }
        */
        return true;
    }

    double rotation;
    double movement;

    //std::cerr << "Swing - stage: " << stage_ << std::endl;

    switch(stage_) {
        case 1:
            rotation = - ticks / 5;
            z_rotate_ += rotation;
            sword_->matrix_obj().rotate_z(rotation);

            movement = -ticks / (double)50;
            x_pos_ += movement;
            sword_->matrix_o2w().translate(movement, 0, 0);


            if(z_rotate_ <= -100) {
                stage_ = 2;
                z_rotate_ = 0;
                x_pos_ = 0;
            }
            break;
        case 2:

            if(z_rotate_ < 80) {
                Matrix4 save_obj = sword_->matrix_obj();
                sword_->matrix_obj().identity();
                sword_->matrix_obj().rotate_z(3);
                sword_->matrix_obj() = sword_->matrix_obj().multiply(save_obj);
                z_rotate_ += 3;
            }

            rotation = -ticks / 3;
            z_rotate_ += rotation;
            sword_->matrix_obj().rotate_y(rotation);

            
            movement = ticks / (double)30;
            x_pos_ += movement;
            sword_->matrix_o2w().translate(movement, 0, 0);

            if(x_pos_ >= 20) {
                stage_ = 3;
                z_rotate_ = 0;
                x_pos_ = 0;
            }

            break;
        case 3:
            Globals::sword2->current_animation()->toggle_pause();
            Globals::particle = new ParticleEffect(Vector3(4, 5, 0));
            stage_ = 4;
            break;
        case 4:
            break;

    }

    /*
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
    */


    //std::cerr << "Bobbing: " << movement << std::endl;

    //sword_->matrix_o2w().translate(0, movement, 0);

    return false;
}

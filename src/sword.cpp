#include <stdlib.h>
#include <cmath>

#include <string>
#include <iostream>
#include "model.h"
#include "matrix4.h"
#include "vector3.h"
#include "vector4.h"
#include "sword.h"

#include "idle_bob.h"

Sword::Sword() : Model()
{

}

Sword::Sword(std::string filename) : Model(filename)
{
    next_animation_ = nullptr;
    current_animation_ = new IdleBob(this);

    parse(filename);
}



void Sword::update(int ticks)
{
    bool return_value;
    if(current_animation_ != nullptr) {
        return_value = current_animation_->update(ticks);

        if(return_value) {
            //delete current_animation_;

            current_animation_ = next_animation_;
            next_animation_ = nullptr;

            if(current_animation_ == nullptr) {
                current_animation_ = new IdleBob(this);
            }
        }

    }
}

void Sword::reset()
{

}

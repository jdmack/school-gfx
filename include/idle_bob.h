#ifndef CSE167_IDLE_BOB_H_
#define CSE167_IDLE_BOB_H_

#include "animation.h"

class Sword;

class IdleBob : public Animation
{
    private:
        double max_height_; 
        double current_height_;
        double height_velocity_;
        int direction_;
        

    public:
        IdleBob();
        IdleBob(Sword * sword);

        bool update(int ticks);



};

#endif

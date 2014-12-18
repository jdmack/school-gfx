#ifndef CSE167_SWING_H_
#define CSE167_SWING_H_

#include "animation.h"

class Sword;

class Swing : public Animation
{
    private:
        double x_pos_; 
        double y_pos_; 
        double z_pos_; 

        double x_rotate_;
        double y_rotate_;
        double z_rotate_;

        int stage_;
        

    public:
        Swing();
        Swing(Sword * sword);

        bool update(int ticks);



};

#endif

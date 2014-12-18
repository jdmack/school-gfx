#ifndef CSE167_SWORD_H_
#define CSE167_SWORD_H_

#include "vector3.h"
#include "model.h"
#include "animation.h"

class Sword : public Model
{
    private:
        Matrix4 matrix_reset_;
        Animation * current_animation_;
        Animation * next_animation_;


    public:

        Sword();
        Sword(std::string filename);

        Animation * current_animation() { return current_animation_; }
        Animation * next_animation() { return next_animation_; }

        void set_current_animation(Animation * a) { current_animation_ = a; }
        void set_next_animation(Animation * a) { next_animation_ = a; }

        void update(int ticks);
        void reset();

};

#endif


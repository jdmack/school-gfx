#ifndef CSE167_SPOT_LIGHT_H_
#define CSE167_SPOT_LIGHT_H_

#include "light.h"

class SpotLight : public Light
{
    private:
        float direction_[3];
        float exponent_[1];
        float cutoff_[1];

    public:
        SpotLight();
        SpotLight(int number);

        // accessors
        float * set_direction() { return direction_; }
        float * exponent() { return exponent_; }
        float * cutoff() { return cutoff_; }

        // mutators
        void set_direction(float x, float y, float z);
        void set_exponent(float exponent) { exponent_[0] = exponent; }
        void set_cutoff(float cutoff) { cutoff_[0] = cutoff; }

        void enable();
        void display();
};


#endif

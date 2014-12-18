#ifndef CSE167_PARTICLE_EFFECT_H_
#define CSE167_PARTICLE_EFFECT_H_

#include <vector>
#include "particle.h"
#include "vector3.h"
#include "object.h"

class ParticleEffect : public Object
{
    private:
        //Vector3 & position()
        std::vector<Particle> particles_;

    public:
        ParticleEffect();
        ParticleEffect(Vector3 point);

        //Vector3 & position() { return position_; }

        //void set_position(Vector3 p) { position_ = p; }

        void display(Camera camera = Camera());
        void update(int ticks = 1);
};

#endif

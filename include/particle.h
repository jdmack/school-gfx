#ifndef CSE167_PARTICLE_H_
#define CSE167_PARTICLE_H_

#include "vector3.h"
#include "color.h"

class Particle
{
    private:
        Vector3 position_;
        Vector3 velocity_;
        Color color_;

        float size_;
        bool alive_;
        int lifetime_;
        int elapsed_time_;

    public:
        Particle();
        Particle(Vector3 point);

        Vector3 & position() { return position_; }
        Vector3 & velocity() { return velocity_; }
        Color & color() { return color_; }
        float size() { return size_; }
        bool alive() { return alive_; }
        int lifetime() { return lifetime_; }
        int elapsed_time() { return elapsed_time_; }

        void set_position(Vector3 p) { position_ = p; }
        void set_velocity(Vector3 v) { velocity_ = v; }
        void set_color(Color color) { color_ = color; }
        void set_size(float size) { size_ = size; }
        void set_alive(bool alive) { alive_ = alive; }
        void set_elapsed_time(int elapsed_time) { elapsed_time_ = elapsed_time; }

        void init();
        void display(Camera camera = Camera());
        void update(int ticks);
};

#endif

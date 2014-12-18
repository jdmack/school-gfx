#include <iostream>
#include "object.h"
#include "camera.h"

#include "particle.h"
#include "particle_effect.h"

#include <GL/glut.h>

ParticleEffect::ParticleEffect() : Object()
{
    //srand(time(NULL));

    int number_of_particles = rand() % 20 + 10;

    std::cerr << "Creating Particle Effect: " << number_of_particles << " particles" << std::endl;

    //particles_ = std::vector<Particle>();

    for(int i = 0; i < number_of_particles; i++) {
        Particle particle = Particle();
        particles_.push_back(particle);
    }

    std::cerr << "ParticleEffect created: " << particles_.size() << std::endl;


}

ParticleEffect::ParticleEffect(Vector3 point) : ParticleEffect()
{
    position_ = point;
    matrix_o2w_.translate(position_.x(), position_.y(), position_.z());
}


void ParticleEffect::display(Camera camera)
{

    //std::cerr << "Displaying ParticleEffect: " << particles_.size() << std::endl;
    start_display(camera);

    for(std::vector<Particle>::iterator it = particles_.begin(); it != particles_.end(); ++it) {
        (*it).display(camera);    
    }


    end_display();

}

void ParticleEffect::update(int ticks)
{
    for(std::vector<Particle>::iterator it = particles_.begin(); it != particles_.end(); ++it) {
        (*it).update(ticks);
    }
}

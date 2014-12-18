#ifndef CSE167_GLOBALS_H_
#define CSE167_GLOBALS_H_

#include "object.h"
#include "camera.h"
#include "light.h"
#include "shader.h"
#include "skybox.h"
#include "floor.h"
#include "model.h"
#include "sphere.h"
#include "cube.h"
#include "sword.h"

class ParticleEffect;

namespace Globals
{
    extern Camera camera;
    extern bool flag;
    extern bool pause;
    extern Matrix4 identity_matrix;

    extern Object * focus;
    extern Light * light1;
    extern Skybox * skybox;
    extern Floor * floor;
    extern Shader * shader;
    extern Shader * particle_shader;
    extern Sphere * sphere;
    extern Cube * cube;
    
    extern Sword * sword1;
    extern Sword * sword2;
    extern Model * arena;

    extern ParticleEffect * particle;
};

#endif


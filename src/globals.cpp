#include "globals.h"
#include "camera.h"
#include "object.h"
#include "light.h"
#include "skybox.h"
#include "floor.h"
#include "shader.h"
#include "sphere.h"
#include "cube.h"
#include "sword.h"

namespace Globals
{
    Camera camera = Camera();
    bool flag = false;
    bool pause = false;
    Matrix4 identity_matrix;

    Object * focus;
    Light * light1;
    Skybox * skybox;
    Floor * floor;
    Shader * shader;
    Sphere * sphere;
    Cube * cube;

    Sword * sword1;
    Sword * sword2;
    Model * arena;

    ParticleEffect * particle;
};

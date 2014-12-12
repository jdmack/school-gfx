#pragma once
#include <vector>
#include "shader.h"
#include "material.h"
#include "vector3.h"
#include <GL/glut.h>

class BezierPatch
{
    private:
        
        Vector3 cp[16];

        Shader * shader_;
        Material material_;

    public:
        BezierPatch();
        BezierPatch(Vector3 *, int x, int y);

        ~BezierPatch();

        Shader * shader() { return shader_; } 
        void set_shader(Shader* shader) { shader_ = shader; }

        Material material() { return material_; } 
        void set_material(Material material) { material_ = material; }

        void set_cp(GLfloat[4][4][3]);

        void display();
        void update();

        GLfloat * Bez(float t, GLfloat * p0, GLfloat * p1, GLfloat * p2, GLfloat * p3);

};


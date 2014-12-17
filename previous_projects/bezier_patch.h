#pragma once
#include <vector>
#include "shader.h"
#include "material.h"
#include "vector3.h"
#include <GL/glut.h>

struct Point {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

static const int detail = 25; // number of points on each curve

class BezierPatch
{
    private:
        
        float time, inc; // used for updating

        GLfloat cp[4][4][3]; // control points
        //Vector3 cp[16];

        GLfloat* indices[detail][detail]; // vertices on curves
        GLfloat* normals[detail][detail];   // normals on curves


        Shader * shader_;
        Material material_;

    public:
        BezierPatch();
        BezierPatch(GLfloat[4][4][3]);
        //BezierPatch(Vector3 *, int x, int y);

        ~BezierPatch();

        Shader * shader() { return shader_; } 
        void set_shader(Shader* shader) { shader_ = shader; }

        Material material() { return material_; } 
        void set_material(Material material) { material_ = material; }

        void set_cp(GLfloat[4][4][3]);

        GLfloat* calculate_u(float t, int row);
        GLfloat* calculate_v(float t, GLfloat** pts);
        GLfloat* calculate(float u, float v);

        GLfloat* calculate_normal(float t1, float t2);


        void display();
        void update();

        GLfloat * Bez(float t, GLfloat * p0, GLfloat * p1, GLfloat * p2, GLfloat * p3);

};


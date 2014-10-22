#ifndef CSE167_CAMERA_H_
#define CSE167_CAMERA_H_

#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"

class Camera
{
    private:
        Vector3 e_;
        Vector3 d_;
        Vector3 up_;
        Matrix4 c_;

    public:
        // constructors
        Camera();
        Camera(Vector3 e, Vector3 d, Vector3 up);

        // accessors
        Vector3 e() const { return e_; }
        Vector3 d() const { return d_; }
        Vector3 up() const { return up_; }
        Matrix4 c() const { return c_; }

        void set_e(Vector3 e) { e_ = e; }
        void set_d(Vector3 d) { d_ = d; }
        void set_up(Vector3 up) { up_ = up; }

        void reset();
        double * gl_matrix();

        void calc();

};

#endif
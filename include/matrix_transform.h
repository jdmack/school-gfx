#ifndef CSE_167_MATRIX_TRANSFORM_H_
#define CSE_167_MATRIX_TRANSFORM_H_

#include "matrix4.h"
#include "group.h"

class MatrixTransform : public Group
{
    protected:
        Matrix4 matrix_;

    public:
        MatrixTransform();
        MatrixTransform(Matrix4 matrix);
        ~MatrixTransform();

        Matrix4 & matrix() { return matrix_; }

        void draw(Matrix4 c);
        void update(int ticks);
        std::pair<Vector3, double> update_bound(Matrix4 c);

};

#endif
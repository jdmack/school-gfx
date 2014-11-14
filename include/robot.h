#ifndef CSE_167_ROBOT_H_
#define CSE_167_ROBOT_H_

#include "node.h"
#include "matrix4.h"
#include "matrix_transform.h"

class Robot : public Node
{
    private:
        MatrixTransform * parts_;
        MatrixTransform * mt_head_ani_;
        MatrixTransform * mt_torso_ani_;
        MatrixTransform * mt_left_arm_ani_;
        MatrixTransform * mt_right_arm_ani_;
        MatrixTransform * mt_left_leg_ani_;
        MatrixTransform * mt_right_leg_ani_;

        int ani_angle_;
        int ani_dir_;

        void setup();

    public:
        Robot();
        ~Robot();
        
        void draw(Matrix4 c);
        void update(int ticks);
        std::pair<Vector3, double> update_bound(Matrix4 c);
};

#endif

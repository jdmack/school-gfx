#ifndef CSE167_SCENE_GRAPH_ROBOT_H_
#define CSE167_SCENE_GRAPH_ROBOT_H_

#include "scene_graph/node.h"
#include "matrix4.h"
#include "scene_graph/matrix_transform.h"

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

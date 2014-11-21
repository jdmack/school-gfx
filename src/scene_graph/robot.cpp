#include "scene_graph/robot.h"
#include "scene_graph/matrix_transform.h"
#include "scene_graph/cube.h"
#include "scene_graph/sphere.h"

Robot::Robot()
{
    parts_ = new MatrixTransform();
    ani_angle_ = 0;
    ani_dir_ = 1;

    setup();
}

Robot::~Robot()
{

}

void Robot::draw(Matrix4 c)
{
    draw_bound();
    parts_->draw(c);
}

void Robot::update(int ticks)
{
    parts_->update(ticks);

    if(ticks != 0) {
        ani_angle_ += (ani_dir_ * 40 / ticks);

        mt_left_arm_ani_->matrix().rotate_x(ani_dir_ * 40 / ticks);
        mt_right_arm_ani_->matrix().rotate_x((-1) * ani_dir_ * 40 / ticks);
        mt_left_leg_ani_->matrix().rotate_x(ani_dir_ * 40/ ticks);
        mt_right_leg_ani_->matrix().rotate_x((-1) * ani_dir_ * 40 / ticks);

        if((ani_angle_ < -65) || (ani_angle_ > 65)) {
            ani_dir_ *= -1;
        }

    }
}

std::pair<Vector3, double> Robot::update_bound(Matrix4 c)
{
    std::pair<Vector3, double> sphere = parts_->update_bound(c);
    center_point_ = sphere.first;
    bound_radius_ = sphere.second;
    return sphere;
}

void Robot::setup()
{
    Matrix4 matrix = Matrix4();

    Cube * head = new Cube();
    //Sphere * head = new Sphere();
    Cube * torso = new Cube();
    Cube * left_arm = new Cube();
    Cube * right_arm = new Cube();
    Cube * left_leg = new Cube();
    Cube * right_leg = new Cube();

    MatrixTransform * mt_head;
    MatrixTransform * mt_torso;
    MatrixTransform * mt_left_arm;
    MatrixTransform * mt_right_arm;
    MatrixTransform * mt_left_leg;
    MatrixTransform * mt_right_leg;

    // HEAD
    matrix.identity();
    matrix.scale(3.0, 3.0, 3.0);
    matrix.translate(0.0, 0.0, 0.0);

    mt_head = new MatrixTransform(matrix);
    mt_head->add_child(head);

    parts_->add_child(mt_head);

    // TORSO
    matrix.identity();
    matrix.scale(5.0, 8.0, 2.0);
    matrix.translate(0.0, -6.0, 0.0);

    mt_torso = new MatrixTransform(matrix);
    mt_torso->add_child(torso);

    parts_->add_child(mt_torso);


    // LEFT ARM
    // Scale and translate
    matrix.identity();
    matrix.scale(1.0, 8.0, 1.0);
    //matrix.translate(3.4, -6.0, 0.0);
    matrix.translate(3.4, -3.0, 0.0);

    mt_left_arm = new MatrixTransform(matrix);
    mt_left_arm->add_child(left_arm);

    // animation matrix
    matrix.identity();
    mt_left_arm_ani_ = new MatrixTransform(matrix);
    mt_left_arm_ani_->add_child(mt_left_arm);

    // translate by 3
    matrix.identity();
    matrix.translate(0.0, -3.0, 0.0);
    mt_left_arm = new MatrixTransform(matrix);
    mt_left_arm->add_child(mt_left_arm_ani_);

    parts_->add_child(mt_left_arm);

    // RIGHT ARM
    // Scale and translate
    matrix.identity();
    matrix.scale(1.0, 8.0, 1.0);
    //matrix.translate(3.4, -6.0, 0.0);
    matrix.translate(-3.4, -3.0, 0.0);

    mt_right_arm = new MatrixTransform(matrix);
    mt_right_arm->add_child(right_arm);

    // animation matrix
    matrix.identity();
    mt_right_arm_ani_ = new MatrixTransform(matrix);
    mt_right_arm_ani_->add_child(mt_right_arm);

    // translate by 3
    matrix.identity();
    matrix.translate(0.0, -3.0, 0.0);
    mt_right_arm = new MatrixTransform(matrix);
    mt_right_arm->add_child(mt_right_arm_ani_);

    parts_->add_child(mt_right_arm);

    // LEFT LEG

    // Scale and translate
    matrix.identity();
    matrix.scale(2.0, 8.0, 2.0);
    matrix.translate(1.7, -3.0, 0.0);

    mt_left_leg = new MatrixTransform(matrix);
    mt_left_leg->add_child(left_leg);

    // animation matrix
    matrix.identity();
    mt_left_leg_ani_ = new MatrixTransform(matrix);
    mt_left_leg_ani_->add_child(mt_left_leg);

    // translate by 11.5
    matrix.identity();
    matrix.translate(0.0, -11.5, 0.0);
    mt_left_leg = new MatrixTransform(matrix);
    mt_left_leg->add_child(mt_left_leg_ani_);

    parts_->add_child(mt_left_leg);

    // RIGHT LEG
    // Scale and translate
    matrix.identity();
    matrix.scale(2.0, 8.0, 2.0);
    matrix.translate(-1.7, -3.0, 0.0);

    mt_right_leg = new MatrixTransform(matrix);
    mt_right_leg->add_child(right_leg);

    // animation matrix
    matrix.identity();
    mt_right_leg_ani_ = new MatrixTransform(matrix);
    mt_right_leg_ani_->add_child(mt_right_leg);

    // translate by 11.5
    matrix.identity();
    matrix.translate(0.0, -11.5, 0.0);
    mt_right_leg = new MatrixTransform(matrix);
    mt_right_leg->add_child(mt_right_leg_ani_);

    parts_->add_child(mt_right_leg);



    //matrix.identity();
    //matrix.scale(2.0, 8.0, 2.0);
    //matrix.translate(-1.7, -14.5, 0.0);

    //mt_right_leg = new MatrixTransform(matrix);
    //mt_right_leg->add_child(right_leg);

    //parts_->add_child(mt_right_leg);

}


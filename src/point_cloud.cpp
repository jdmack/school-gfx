#include <stdlib.h>
#include <GL/glut.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "point_cloud.h"
#include "object.h"
#include "matrix4.h"
#include "camera.h"

PointCloud::PointCloud() : Object()
{
    largest_x_ = 0;
    largest_y_ = 0;
    largest_z_ = 0;
    smallest_x_ = 0;
    smallest_y_ = 0;
    smallest_z_ = 0;

}

PointCloud::PointCloud(std::string filename) : Object()
{
    largest_x_ = 0;
    largest_y_ = 0;
    largest_z_ = 0;
    smallest_x_ = 0;
    smallest_y_ = 0;
    smallest_z_ = 0;

    parse(filename);
}


void PointCloud::display(Camera camera)
{
    glMatrixMode(GL_MODELVIEW);         // make sure we're in Objectview mode

    // Tell OpenGL what ObjectView matrix to use:
    matrix().identity();
    matrix().set(matrix().multiply(matrix_obj()));
    matrix().set(matrix().multiply(matrix_o2w()));
    matrix().set(matrix().multiply(camera.c()));
    glLoadMatrixd(matrix().pointer());

    glColor3f(0.0, 1.0, 0.0);		// Set cloud green

    // Draw point cloud
    glBegin(GL_POINTS);

    for(unsigned int i = 0; i < points_.size(); i++) {
        glNormal3d(normals_[i].x(), normals_[i].y(), normals_[i].z());
        glVertex3d(points_[i].x(), points_[i].y(), points_[i].z());
    }
    glEnd();
}

void PointCloud::update(int ticks)
{
}

void PointCloud::reset()
{
    Object::reset();

    double translate_x = 0 - center_.x();
    double translate_y = 0 - center_.y();
    double translate_z = 0 - center_.z();

    matrix_obj_.translate(translate_x, translate_y, translate_z);
    matrix_obj_.scale(100.0, 100.0, 100.0);
}

void PointCloud::parse(std::string filename)
{
    std::cout << "Reading File: " << filename << std::endl;
    std::ifstream file(filename.c_str());

    if(!file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    while(!file.eof()) {
        Vector3 point;
        Vector3 normal;

        file >> point.x();
        file >> point.y();
        file >> point.z();

        file >> normal.x();
        file >> normal.y();
        file >> normal.z();

        if(file.eof()) break;

        normal.normalize();

        points_.push_back(point);
        normals_.push_back(normal);
        //std::cout << "Reading in Point" << point.str() << " Normal" << normal.str() << std::endl;
    }

    calculate_dim();
    reset();
}

void PointCloud::calculate_dim()
{

    for(unsigned int i = 0; i < points_.size(); i++) {

        if(points_[i].x() > largest_x_) {
            largest_x_ = points_[i].x();
        }
        if(points_[i].y() > largest_y_) {
            largest_y_ = points_[i].y();
        }
        if(points_[i].z() > largest_z_) {
            largest_z_ = points_[i].z();
        }
        if(points_[i].x() < smallest_x_) {
            smallest_x_ = points_[i].x();
        }
        if(points_[i].y() < smallest_y_) {
            smallest_y_ = points_[i].y();
        }
        if(points_[i].z() < smallest_z_) {
            smallest_z_ = points_[i].z();
        }
    }

    double mid_x = largest_x_ - ((largest_x_ - smallest_x_) / 2);
    double mid_y = largest_y_ - ((largest_y_ - smallest_y_) / 2);
    double mid_z = largest_z_ - ((largest_z_ - smallest_z_) / 2);
    center_ = Vector3(mid_x, mid_y, mid_z);

    std::cout << "x range: [" << smallest_x_ << ", " << largest_x_ << "]" << std::endl;
    std::cout << "y range: [" << smallest_y_ << ", " << largest_y_ << "]" << std::endl;
    std::cout << "z range: [" << smallest_z_ << ", " << largest_z_ << "]" << std::endl;
    std::cout << "center: " << center_.str() << std::endl;
}


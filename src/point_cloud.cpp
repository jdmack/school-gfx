#include <stdlib.h>
#include <cmath>
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

}

PointCloud::PointCloud(std::string filename) : Object()
{

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
    glDisable(GL_LIGHTING);

    // Draw point cloud
    glBegin(GL_POINTS);

    for(unsigned int i = 0; i < points_.size(); i++) {
        glColor3f(normals_[i].x(), normals_[i].y(), normals_[i].z());
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
    calculate_scale();
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

        if(points_[i].x() > largest_x_.x()) {
            largest_x_ = points_[i];
        }
        if(points_[i].y() > largest_y_.y()) {
            largest_y_ = points_[i];
        }
        if(points_[i].z() > largest_z_.z()) {
            largest_z_ = points_[i];
        }
        if(points_[i].x() < smallest_x_.x()) {
            smallest_x_ = points_[i];
        }
        if(points_[i].y() < smallest_y_.y()) {
            smallest_y_ = points_[i];
        }
        if(points_[i].z() < smallest_z_.z()) {
            smallest_z_ = points_[i];
        }
    }

    double mid_x = (largest_x_.x() + smallest_x_.x()) / 2;
    double mid_y = (largest_y_.y() + smallest_y_.y()) / 2;
    double mid_z = (largest_z_.z() + smallest_z_.z()) / 2;
    center_ = Vector3(mid_x, mid_y, mid_z);

    std::cout << "x range: [" << smallest_x_.x() << ", " << largest_x_.x() << "]" << std::endl;
    std::cout << "y range: [" << smallest_y_.y() << ", " << largest_y_.y() << "]" << std::endl;
    std::cout << "z range: [" << smallest_z_.z() << ", " << largest_z_.z() << "]" << std::endl;
    std::cout << "center: " << center_.str() << std::endl;

    // TRANSLATE for CENTERING
    double translate_x = 0 - center_.x();
    double translate_y = 0 - center_.y();
    double translate_z = 0 - center_.z();

    matrix_o2w_.translate(translate_x, translate_y, translate_z);
    std::cout << "Translate Matrix: " << std::endl;
    matrix_o2w_.print();

    for(unsigned int i = 0; i < points_.size(); i++) {
        points_[i].transform(matrix_o2w_);
    }
    largest_x_.transform(matrix_o2w_);
    smallest_x_.transform(matrix_o2w_);
    largest_y_.transform(matrix_o2w_);
    smallest_y_.transform(matrix_o2w_);
    largest_z_.transform(matrix_o2w_);
    smallest_z_.transform(matrix_o2w_);
    
    matrix_o2w_.identity();
}

void PointCloud::calculate_scale()
{
    double screen_width = 18;
    double screen_height = 20;

    double width = std::abs(smallest_x_.x()) + std::abs(largest_x_.x());
    double height = std::abs(smallest_y_.y()) + std::abs(largest_y_.y());
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    
    double x_scale = screen_width / width;
    double y_scale = screen_height / height;
    
    if(x_scale < y_scale) {
        matrix_obj_.scale(x_scale, x_scale, x_scale);
    }
    else {
        matrix_obj_.scale(y_scale, y_scale, y_scale);
    }
    
    std::cout << "Scale Matrix: " << std::endl;
    matrix_obj_.print();
}


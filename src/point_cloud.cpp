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

    // Draw point cloud
    glBegin(GL_POINTS);

    for(int i = 0; i < points_.size(); i++) {
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

        if(file.eof()) return;

        normal.normalize();

        points_.push_back(point);
        normals_.push_back(normal);
        //std::cout << "Reading in Point" << point.str() << " Normal" << normal.str() << std::endl;
    }
}


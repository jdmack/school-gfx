#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "model.h"
#include "matrix4.h"
#include "camera.h"
#include "object.h"

Model::Model() : Object()
{

}

Model::Model(std::string filename) : Object()
{

    parse(filename);
}


void Model::display(Camera camera)
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
    glPointSize(5);

    // Draw point cloud
    glBegin(GL_TRIANGLES);

    for(unsigned int i = 0; i < faces_.size(); i++) {
        //glColor3f(normals_[i].x(), normals_[i].y(), normals_[i].z());

        //glNormal3d(normals_[i].x(), normals_[i].y(), normals_[i].z());

        glVertex3d(faces_[i].vertex1().x(), faces_[i].vertex1().y(), faces_[i].vertex1().z());
        glVertex3d(faces_[i].vertex2().x(), faces_[i].vertex2().y(), faces_[i].vertex2().z());
        glVertex3d(faces_[i].vertex3().x(), faces_[i].vertex3().y(), faces_[i].vertex3().z());
    }
    glEnd();
}

void Model::update(int ticks)
{
}

void Model::reset()
{
    Object::reset();
}

void Model::parse(std::string filename)
{
    FILE * file_p;

    float x, y, z;
    float r, g, b;
    int v1, v2, v3;
    int n1, n2, n3;
    int c1, c2;

    file_p = fopen( filename.c_str(), "rb");
    if(file_p == NULL) {
        std::cerr << "Error: Could not open file: " << filename << std::endl;
        exit(-1); 
    }

    while((c1 = fgetc(file_p)) != EOF) {
        c2 = fgetc(file_p);

        if((c1 == 'v') && (c2 == ' ')) {
            fscanf(file_p, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
            vertices_.push_back(Vector3(x, y, z));
        }
        else if((c1 == 'v') && (c2 == 'n')) {
            fscanf(file_p, "%f %f %f ", &x, &y, &z);
            normals_.push_back(Vector3(x, y, z));
        }
        else if((c1 == 'f') && (c2 == ' ')) {
            fscanf(file_p, "%d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);
            
            v1 -= 1;
            v2 -= 1;
            v3 -= 1;
            n1 -= 1;
            n2 -= 1;
            n3 -= 1;


            if((v1 >= vertices_.size()) || (v2 >= vertices_.size()) || (v3 >= vertices_.size())) {
                std::cerr << "Error: Vertices out of range: " << v1 << ", " << v2 << ", " << v3 << std::endl;
                continue;
            }
            if((n1 >= normals_.size()) || (n2 >= normals_.size()) || (n3 >= normals_.size())) {
                std::cerr << "Error: Normals out of range: " << n1 << ", " << n2 << ", " << n3 << std::endl;
                continue;
            }
            faces_.push_back(Triangle(vertices_[v1], normals_[n1], vertices_[v2], normals_[n2], vertices_[v3], normals_[n3]));
        }
    }

    fclose(file_p);   // make sure you don't forget to close the file when done
}



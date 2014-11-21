#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
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
    material_.render();

    glMatrixMode(GL_MODELVIEW);         // make sure we're in Objectview mode

    // Tell OpenGL what ObjectView matrix to use:
    matrix().identity();
    matrix().set(matrix().multiply(matrix_obj()));
    matrix().set(matrix().multiply(matrix_o2w()));
    matrix().set(matrix().multiply(camera.c()));
    glLoadMatrixd(matrix().pointer());

    // Draw point cloud
    glBegin(GL_TRIANGLES);

    for(unsigned int i = 0; i < faces_.size(); i++) {
        glColor3d(faces_[i].color1().r(), faces_[i].color1().g(), faces_[i].color1().b());
        //glColor3d(faces_[i].normal1().x(), faces_[i].normal1().y(), faces_[i].normal1().z());

        //glColor3d(1.0, 1.0, 1.0);

        //glNormal3d(normals_[i].x(), normals_[i].y(), normals_[i].z());

        glNormal3d(faces_[i].normal1().x(), faces_[i].normal1().y(), faces_[i].normal1().z());
        glVertex3d(faces_[i].vertex1().x(), faces_[i].vertex1().y(), faces_[i].vertex1().z());

        glNormal3d(faces_[i].normal2().x(), faces_[i].normal2().y(), faces_[i].normal2().z());
        glVertex3d(faces_[i].vertex2().x(), faces_[i].vertex2().y(), faces_[i].vertex2().z());

        glNormal3d(faces_[i].normal3().x(), faces_[i].normal3().y(), faces_[i].normal3().z());
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
    calculate_scale();
}

void Model::parse(std::string filename)
{
    std::cerr << "Reading File: " << filename << std::endl;

    FILE * file_p;

    double x, y, z;
    double r, g, b;
    int v1, v2, v3;
    int n1, n2, n3;
    int c1, c2;

    std::ifstream infile(filename);

    if(!infile.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        exit(-1);
        return;
    }

    std::string line;
    std::vector<std::string> tokens;
    std::string token;

    while(std::getline(infile, line)) {
        //std::cerr << "Parsing: " << line << std::endl;
        tokens = split(line, ' ');
        if(tokens.size() <= 0) continue;

        if(tokens.at(0).compare("v") == 0) {
            //Parse rest of tokens into doubles
            x = std::stod(tokens.at(1));
            y = std::stod(tokens.at(2));
            z = std::stod(tokens.at(3));

            if(tokens.size() == 7) {
                r = std::stod(tokens.at(4));
                g = std::stod(tokens.at(5));
                b = std::stod(tokens.at(6));
            }
            else {
                r = 1.0;
                g = 1.0;
                b = 1.0;
            }

            vertices_.push_back(Vector3(x, y, z));
            colors_.push_back(Color(r, g, b));
        }

        else if(tokens.at(0).compare("vn") == 0) {
            x = std::stod(tokens.at(1));
            y = std::stod(tokens.at(2));
            z = std::stod(tokens.at(3));

            Vector3 normal = Vector3(x, y, z);
            normal.normalize();
            normals_.push_back(normal);
        }
        else if(tokens.at(0).compare("f") == 0) {

            std::vector<std::string> face_tokens;

            token = tokens.at(1);
            face_tokens = split(token, '//');
            if(face_tokens.size() >= 3) {
                //std::cerr << "token 0: " << face_tokens.at(0) << std::endl;
                //std::cerr << "token 1: " << face_tokens.at(1) << std::endl;
                //std::cerr << "token 2: " << face_tokens.at(2) << std::endl;
                //std::cerr << "tokens: " << face_tokens.size() << std::endl;
                v1 = std::stoi(face_tokens.at(0)) - 1;
                n1 = std::stoi(face_tokens.at(2)) - 1;
            }
            
            token = tokens.at(2);
            face_tokens = split(token, '//');
            if(face_tokens.size() >= 3) {
                v2 = std::stoi(face_tokens.at(0)) - 1;
                n2 = std::stoi(face_tokens.at(2)) - 1;
            }
            
            token = tokens.at(3);
            face_tokens = split(token, '//');
            if(face_tokens.size() >= 3) {
                v3 = std::stoi(face_tokens.at(0)) - 1;
                n3 = std::stoi(face_tokens.at(2)) - 1;
            }


            if((v1 >= vertices_.size()) || (v2 >= vertices_.size()) || (v3 >= vertices_.size())) {
                std::cerr << "Error: Vertices out of range: " << v1 << ", " << v2 << ", " << v3 << std::endl;
                continue;
            }
            if((n1 >= normals_.size()) || (n2 >= normals_.size()) || (n3 >= normals_.size())) {
                std::cerr << "Error: Normals out of range: " << n1 << ", " << n2 << ", " << n3 << std::endl;
                continue;
            }
            faces_.push_back(Triangle(vertices_[v1], normals_[n1], colors_[v1], vertices_[v2], normals_[n2], colors_[v2], vertices_[v3], normals_[n3], colors_[v3]));
        }
    


    }






    std::cerr << "Vertices: " << vertices_.size() << std::endl;
    std::cerr << "Normals: " << normals_.size() << std::endl;
    std::cerr << "Colors: " << colors_.size() << std::endl;
    std::cerr << "Faces: " << faces_.size() << std::endl;


    calculate_dim();
    reset();

    std::cout << "Scale Matrix: " << std::endl;
    matrix_obj_.print();
}

/*
void Model::parse(std::string filename)
{
    std::cerr << "Reading File: " << filename << std::endl;

    FILE * file_p;

    float x, y, z;
    float r, g, b;
    int v1, v2, v3;
    int n1, n2, n3;
    int c1, c2;

    int matches;

    file_p = fopen( filename.c_str(), "rb");
    if(file_p == NULL) {
        std::cerr << "Error: Could not open file: " << filename << std::endl;
        exit(-1); 
    }

    while((c1 = fgetc(file_p)) != EOF) {
        c2 = fgetc(file_p);

        if((c1 == 'v') && (c2 == ' ')) {
            matches = fscanf(file_p, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
            //std::cerr << "Matches: " << matches << std::endl;
            if(matches == 3) {
                r = 1.0;
                g = 1.0;
                b = 1.0;
            }
            vertices_.push_back(Vector3(x, y, z));
            colors_.push_back(Color(r, g, b));
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
            faces_.push_back(Triangle(vertices_[v1], normals_[n1], colors_[v1], vertices_[v2], normals_[n2], colors_[v2], vertices_[v3], normals_[n3], colors_[v3]));
        }
    }
    std::cerr << "Vertices: " << vertices_.size() << std::endl;
    std::cerr << "Normals: " << normals_.size() << std::endl;
    std::cerr << "Colors: " << colors_.size() << std::endl;
    std::cerr << "Faces: " << faces_.size() << std::endl;

    fclose(file_p);

    calculate_dim();
    reset();

    std::cout << "Scale Matrix: " << std::endl;
    matrix_obj_.print();
}
*/

void Model::calculate_dim()
{

    for(unsigned int i = 0; i < vertices_.size(); i++) {

        if(vertices_[i].x() > largest_x_.x()) {
            largest_x_ = vertices_[i];
        }
        if(vertices_[i].y() > largest_y_.y()) {
            largest_y_ = vertices_[i];
        }
        if(vertices_[i].z() > largest_z_.z()) {
            largest_z_ = vertices_[i];
        }
        if(vertices_[i].x() < smallest_x_.x()) {
            smallest_x_ = vertices_[i];
        }
        if(vertices_[i].y() < smallest_y_.y()) {
            smallest_y_ = vertices_[i];
        }
        if(vertices_[i].z() < smallest_z_.z()) {
            smallest_z_ = vertices_[i];
        }
    }

    double mid_x = (largest_x_.x() + smallest_x_.x()) / 2;
    double mid_y = (largest_y_.y() + smallest_y_.y()) / 2;
    double mid_z = (largest_z_.z() + smallest_z_.z()) / 2;
    center_ = Vector3(mid_x, mid_y, mid_z);

    std::cout << "X range: [" << smallest_x_.x() << ", " << largest_x_.x() << "]" << std::endl;
    std::cout << "Y range: [" << smallest_y_.y() << ", " << largest_y_.y() << "]" << std::endl;
    std::cout << "Z range: [" << smallest_z_.z() << ", " << largest_z_.z() << "]" << std::endl;
    std::cout << "Center: " << center_.str() << std::endl;

    // TRANSLATE for CENTERING
    double translate_x = 0 - center_.x();
    double translate_y = 0 - center_.y();
    double translate_z = 0 - center_.z();

    matrix_o2w_.translate(translate_x, translate_y, translate_z);
    std::cout << "Translate Matrix: " << std::endl;
    matrix_o2w_.print();

    for(unsigned int i = 0; i < vertices_.size(); i++) {
        vertices_[i].transform(matrix_o2w_);
    }
    largest_x_.transform(matrix_o2w_);
    smallest_x_.transform(matrix_o2w_);
    largest_y_.transform(matrix_o2w_);
    smallest_y_.transform(matrix_o2w_);
    largest_z_.transform(matrix_o2w_);
    smallest_z_.transform(matrix_o2w_);

    matrix_o2w_.identity();
}

void Model::calculate_scale()
{
    double screen_width = 18;
    double screen_height = 20;

    double width = std::abs(smallest_x_.x()) + std::abs(largest_x_.x());
    double height = std::abs(smallest_y_.y()) + std::abs(largest_y_.y());
    //std::cout << "Width: " << width << std::endl;
    //std::cout << "Height: " << height << std::endl;

    double x_scale = screen_width / width;
    double y_scale = screen_height / height;

    if(x_scale < y_scale) {
        matrix_obj_.scale(x_scale, x_scale, x_scale);
    }
    else {
        matrix_obj_.scale(y_scale, y_scale, y_scale);
    }

    // TRANSLATE for CENTERING
    double translate_x = 0 - center_.x();
    double translate_y = 0 - center_.y();
    double translate_z = 0 - center_.z();

    matrix_o2w_.translate(translate_x, translate_y, translate_z);
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string> & Model::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> Model::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

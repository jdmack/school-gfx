#include <iostream>
#include "group.h"
#include "globals.h"

Group::Group()
{

}

Group::~Group()
{

}

void Group::add_child(Node * node)
{
    children_.push_back(node);
}

void Group::remove_child(Node * node)
{
    for(std::list<Node *>::iterator it = children_.begin(); it != children_.end(); ++it) {
        if((*it) == node) {
            children_.erase(it);
        }
    }
}

void Group::draw(Matrix4 c)
{
    if(Globals::frustum.sphereInFrustum(center_point_, bound_radius_)) {
        //std::cerr << "In frustum" << std::endl;
        for(std::list<Node *>::iterator it = children_.begin(); it != children_.end(); ++it) {
            (*it)->draw(c);
        }
    }
}

void Group::update(int ticks)
{
    for(std::list<Node *>::iterator it = children_.begin(); it != children_.end(); ++it) {
        (*it)->update(ticks);
    }
}

std::pair<Vector3, double> Group::update_bound(Matrix4 c)
{
    std::list<Vector3> center_points;
    std::list<double> radiuses;
    for(std::list<Node *>::iterator it = children_.begin(); it != children_.end(); ++it) {
        std::pair<Vector3, double> pair = (*it)->update_bound(c);
        center_points.push_back(pair.first);
        radiuses.push_back(pair.second);
    }

    /*
    double min_x = 0;
    double max_x = 0;
    double min_y = 0;
    double max_y = 0;
    double min_z = 0;
    double max_z = 0;

    // Find center point
    for(std::list<Vector3>::iterator it = center_points.begin(); it != center_points.end(); ++it) {
        if((*it).x() < min_x) min_x = (*it).x(); 
        if((*it).x() > max_x) max_x = (*it).x(); 
        if((*it).y() < min_y) min_y = (*it).y(); 
        if((*it).y() > max_y) max_y = (*it).y(); 
        if((*it).z() < min_z) min_z = (*it).z(); 
        if((*it).z() > max_z) max_z = (*it).z(); 
    }

    center_point_ = Vector3((max_x + min_x) / 2, (max_y + min_y) / 2, (max_z + min_z) / 2);
    
    double max_radius = 0;

    // Find largest radius
    for(std::list<double>::iterator it = radiuses.begin(); it != radiuses.end(); ++it) {
        if((*it) > max_radius) max_radius = (*it);
    }
    
    Vector3 max_point = Vector3(max_x, max_y, max_z);
    Vector3 min_point = Vector3(min_x, min_y, min_z);

    bound_radius_ = max_point.distance_from(min_point) / 2 + max_radius;

*/
    return std::make_pair(center_point_, bound_radius_);
}


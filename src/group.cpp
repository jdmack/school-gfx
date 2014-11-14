#include <iostream>
#include "group.h"

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
    //std::cerr << name_ << " - Group::draw()" << std::endl;
    for(std::list<Node *>::iterator it = children_.begin(); it != children_.end(); ++it) {
        (*it)->draw(c);
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
    for(std::list<Node *>::iterator it = children_.begin(); it != children_.end(); ++it) {
        (*it)->update_bound(c);
    }

    Vector3 center_point;
    double radius;
    std::pair<Vector3, double> sphere = std::make_pair(center_point, radius);
    return sphere;

}


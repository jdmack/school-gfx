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

void Group::update()
{

}

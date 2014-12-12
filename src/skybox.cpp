#include <iostream>
#include <cmath>

#include "glee.h"
#include "skybox.h"
#include "texture.h"


Skybox::Skybox(double radius)
{
	size_ = radius;
	
	init();
	
}

void Skybox::init()
{
    // FRONT
    front_texture_ = new Texture(texture_front);

    // BACk
    back_texture_ = new Texture(texture_back);

    // LEFT
    left_texture_ = new Texture(texture_left);

    // RIGHT
    right_texture_ = new Texture(texture_right);

    // TOP
    top_texture_ = new Texture(texture_top);

    // BOTTOM
    bottom_texture_ = new Texture(texture_bottom);


	//skyShader = new Shader("shader/skybox.vert", "shader/skybox.frag");

}

void Skybox::update()
{

}

void Skybox::display()
{

    Object::display();
	//skyShader->bind();

    // FRONT
    front_texture_->bind();
	glBegin(GL_QUADS);

    glTexCoord2f(1, 1);
	glVertex3f(+size_, -size_, +size_);     // bottom right

    glTexCoord2f(0, 1);
	glVertex3f(-size_, -size_, +size_);     // bottom left

    glTexCoord2f(0, 0);
	glVertex3f(-size_, +size_, +size_);     // top left

    glTexCoord2f(1, 0);
	glVertex3f(+size_, +size_, +size_);     // top right

	glEnd();
    front_texture_->unbind();

    // BACK
    back_texture_->bind();
	glBegin(GL_QUADS);

    glTexCoord2f(1, 1);
	glVertex3f(-size_, -size_, -size_);     // bottom left

    glTexCoord2f(0, 1);
	glVertex3f(+size_, -size_, -size_);     // bottom left

    glTexCoord2f(0, 0);
	glVertex3f(+size_, +size_, -size_);     // top right

    glTexCoord2f(1, 0);
	glVertex3f(-size_, +size_, -size_);     // top left

	glEnd();
    back_texture_->unbind();

    // LEFT
    left_texture_->bind();
	glBegin(GL_QUADS);

    glTexCoord2f(1, 1);
	glVertex3f(-size_, -size_, +size_);     // far bottom

    glTexCoord2f(0, 1);
	glVertex3f(-size_, -size_, -size_);     // near bottom

    glTexCoord2f(0, 0);
	glVertex3f(-size_, +size_, -size_);     // near top

    glTexCoord2f(1, 0);
	glVertex3f(-size_, +size_, +size_);     // far top

	glEnd();
    left_texture_->unbind();

    // RIGHT
    right_texture_->bind();
	glBegin(GL_QUADS);

    glTexCoord2f(1, 1);
	glVertex3f(+size_, -size_, -size_);     // near bottom

    glTexCoord2f(0, 1);
	glVertex3f(+size_, -size_, +size_);     // far bottom

    glTexCoord2f(0, 0);
	glVertex3f(+size_, +size_, +size_);     // far top

    glTexCoord2f(1, 0);
	glVertex3f(+size_, +size_, -size_);     // near top

	glEnd();
    right_texture_->unbind();

    // TOP
    top_texture_->bind();
	glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
	glVertex3f(-size_, +size_, -size_);     // near left

    glTexCoord2f(1, 0);
	glVertex3f(+size_, +size_, -size_);     // near right

    glTexCoord2f(1, 1);
	glVertex3f(+size_, +size_, +size_);     // far  right

    glTexCoord2f(0, 1);
	glVertex3f(-size_, +size_, +size_);     // far left

	glEnd();
    top_texture_->unbind();

    // BOTOM
    bottom_texture_->bind();
	glBegin(GL_QUADS);

    glTexCoord2f(1, 1);
	glVertex3f(+size_, -size_, -size_);     // near right

    glTexCoord2f(0, 1);
	glVertex3f(-size_, -size_, -size_);     // near left

    glTexCoord2f(0, 0);
	glVertex3f(-size_, -size_, +size_);     // far left

    glTexCoord2f(1, 0);
	glVertex3f(+size_, -size_, +size_);     // far right

	glEnd();
    bottom_texture_->unbind();

	//skyShader->unbind();
}


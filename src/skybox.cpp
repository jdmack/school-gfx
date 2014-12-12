#include <iostream>
#include <cmath>

#include "glee.h"
#include "skybox.h"
#include "texture.h"


Skybox::Skybox(double radius)
{
	size_ = radius;
	for(int i = 0; i < 6; i++){
		facePresent[i] = false;
	}

	float SkyBoxVertices[] =
	{	// x, y, z, x, y, z, x, y, z, x, y, z
		1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, // +X
		-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, // -X
		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, // +Y
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // -Y
		1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // +Z
		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f  // -Z
	};

	//glGenBuffers(1, &SkyBoxVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, SkyBoxVBO);
	//glBufferData(GL_ARRAY_BUFFER, 288, SkyBoxVertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	
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
    //bottom_texture_ = new Texture(texture_bottom);


	//skyShader = new Shader("shader/skybox.vert", "shader/skybox.frag");

}

void Skybox::update()
{

}

void Skybox::display(){

    Object::display();
	//skyShader->bind();

	glBegin(GL_QUADS);

    // FRONT
    front_texture_->bind();

    glTexCoord2f(1, 1);
	glVertex3f(+size_, -size_, +size_);     // bottom right

    glTexCoord2f(0, 1);
	glVertex3f(-size_, -size_, +size_);     // bottom left

    glTexCoord2f(0, 0);
	glVertex3f(-size_, +size_, +size_);     // top left

    glTexCoord2f(1, 0);
	glVertex3f(+size_, +size_, +size_);     // top right

    front_texture_->unbind();

    // BACK
    back_texture_->bind();

    glTexCoord2f(1, 1);
	glVertex3f(-size_, -size_, -size_);     // bottom left

    glTexCoord2f(0, 1);
	glVertex3f(+size_, -size_, -size_);     // bottom left

    glTexCoord2f(0, 0);
	glVertex3f(+size_, +size_, -size_);     // top right

    glTexCoord2f(1, 0);
	glVertex3f(-size_, +size_, -size_);     // top left

    back_texture_->unbind();

    // LEFT
    left_texture_->bind();

    glTexCoord2f(1, 1);
	glVertex3f(-size_, -size_, +size_);     // far bottom

    glTexCoord2f(0, 1);
	glVertex3f(-size_, -size_, -size_);     // near bottom

    glTexCoord2f(0, 0);
	glVertex3f(-size_, +size_, -size_);     // near top

    glTexCoord2f(1, 0);
	glVertex3f(-size_, +size_, +size_);     // far top

    left_texture_->unbind();

    // RIGHT
    right_texture_->bind();

    glTexCoord2f(1, 1);
	glVertex3f(+size_, -size_, -size_);     // near bottom

    glTexCoord2f(0, 1);
	glVertex3f(+size_, -size_, +size_);     // far bottom

    glTexCoord2f(0, 0);
	glVertex3f(+size_, +size_, +size_);     // far top

    glTexCoord2f(1, 0);
	glVertex3f(+size_, +size_, -size_);     // near top

    right_texture_->unbind();

    // TOP
    top_texture_->bind();

    glTexCoord2f(1, 1);
	glVertex3f(-size_, +size_, -size_);     // near left

    glTexCoord2f(0, 1);
	glVertex3f(+size_, +size_, -size_);     // near right

    glTexCoord2f(0, 0);
	glVertex3f(+size_, +size_, +size_);     // far  right

    glTexCoord2f(1, 0);
	glVertex3f(-size_, +size_, +size_);     // far left

    top_texture_->unbind();

    // BOTOM
	//glVertex3f(+size_, -size_, -size_);       //
	//glVertex3f(-size_, -size_, -size_);       //
	//glVertex3f(-size_, -size_, +size_);       //
	//glVertex3f(+size_, -size_, +size_);       //

	glEnd();
	//skyShader->unbind();
}

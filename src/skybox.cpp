#include "shader.h"
#include "skybox.h"
#include <iostream>

Skybox::Skybox(float size)
{
    size_ = size;

    use_map_ = true;
    //use_map_ = false;


    init();
}


void Skybox::init()
{
    //front_texture_ = new Texture(texture_front);
    //back_texture_ = new Texture(texture_back);
    //left_texture_ = new Texture(texture_left);
    //right_texture_ = new Texture(texture_right);
    //top_texture_ = new Texture(texture_top);
    //bottom_texture_ = new Texture(texture_bottom);

	float points[] = {
		-size_,  size_, -size_,
		-size_, -size_, -size_,
		 size_, -size_, -size_,
		 size_, -size_, -size_,
		 size_,  size_, -size_,
		-size_,  size_, -size_,

		-size_, -size_,  size_,
		-size_, -size_, -size_,
		-size_,  size_, -size_,
		-size_,  size_, -size_,
		-size_,  size_,  size_,
		-size_, -size_,  size_,

		 size_, -size_, -size_,
		 size_, -size_,  size_,
		 size_,  size_,  size_,
		 size_,  size_,  size_,
		 size_,  size_, -size_,
		 size_, -size_, -size_,

		-size_, -size_,  size_,
		-size_,  size_,  size_,
		 size_,  size_,  size_,
		 size_,  size_,  size_,
		 size_, -size_,  size_,
		-size_, -size_,  size_,

		-size_,  size_, -size_,
		 size_,  size_, -size_,
		 size_,  size_,  size_,
		 size_,  size_,  size_,
		-size_,  size_,  size_,
		-size_,  size_, -size_,

		-size_, -size_, -size_,
		-size_, -size_,  size_,
		 size_, -size_, -size_,
		 size_, -size_, -size_,
		-size_, -size_,  size_,
		 size_, -size_,  size_
	};
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    shader_ = new Shader("shader/skybox.vert", "shader/skybox.frag");


    // original
    //create_cube_map(texture_front, texture_back, texture_top, texture_bottom, texture_left, texture_right, skybox);

    create_cube_map(texture_back, texture_front, texture_top, texture_bottom, texture_left, texture_right, skybox);

    /*
    createCubeMap("texture/PalldioPalace_extern_front.ppm",
        "texture/PalldioPalace_extern_back.ppm",
        "texture/PalldioPalace_extern_left.ppm",
        "texture/PalldioPalace_extern_right.ppm",
        "texture/PalldioPalace_extern_top.ppm",
        "texture/PalldioPalace_extern_base.ppm",
        skybox);
    */
}

void Skybox::update()
{

}


void Skybox::create_cube_map(std::string front, std::string back, std::string top, std::string bottom, std::string left, std::string right, GLuint* tex_cube) 
{

    // generate a cube-map texture to hold all the sides
	glActiveTexture(GL_TEXTURE0);

    // Create ID for texture
	glGenTextures(1, tex_cube);
    std::cerr << "CubeMap id: " << tex_cube << std::endl;


    // load each image and copy into a side of the cube-map texture
	load_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
	load_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
	load_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
	load_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
	load_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
	load_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// format cube map texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Skybox::load_side(GLuint texture, GLenum side_target, std::string filename) 
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    int width, height;     // texture width/height [pixels]
    unsigned char * data;  // texture pixel data

	//FILE *file;

	// open texture data
	//file = fopen(filename, "rb");
	//if (file == NULL) {
		//printf("Error reading from file \"%s\". Please ensure it exists and try again.\n", filename);
		//cin.get();
		//exit(1);
	//}
	// allocate buffer
	//data = (unsigned char*)malloc(2048 * 2048 * 4);

	// read texture data
	//fread(data, 2048 * 2048 * 4, 1, file);
	//fclose(file);

    data = load_PPM(filename.c_str(), width, height);

    if(data == NULL) {
        std:: cerr << "Error: could not load " << filename << std::endl;
        return;
    }
    // non-power-of-2 dimensions check
    if ((width & (width - 1)) != 0 || (height & (height - 1)) != 0) {
        std:: cerr << "WARNING: image " << filename << " is not power-of-2 dimensions" << std::endl;
    }


    std::cerr << "Width, Height: " << width << ", " << height << std::endl;

	// copy image data into 'target' side of cube map
	glTexImage2D(side_target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//free(data);
}



void Skybox::display()
{

    Object::display();

    if(use_map_) {

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glDisable(GL_BLEND);

        shader_->bind();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox[0]);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


        shader_->unbind();

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_BLEND);

        glDisable(GL_TEXTURE_2D);
    }
    else {
/*
        shader_->bind();

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
*/

    }
}

/** Load a ppm file from disk.
    @input filename The location of the PPM file.  If the file is not found, an error message
        will be printed and this function will return 0
    @input width This will be modified to contain the width of the loaded image, or 0 if file not found
    @input height This will be modified to contain the height of the loaded image, or 0 if file not found
    @return Returns the RGB pixel data as interleaved unsigned chars (R0 G0 B0 R1 G1 B1 R2 G2 B2 .... etc) or 0 if an error ocured
**/

unsigned char * Skybox::load_PPM(const char * filename, int & width, int & height)
{
    const int BUFSIZE = 128;
    FILE* fp;
    unsigned int read;
    unsigned char* rawData;
    char buf[3][BUFSIZE];
    //char* retval_fgets;
    //size_t retval_sscanf;

    if((fp=fopen(filename, "rb")) == NULL) {
        std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
        width = 0;
        height = 0;
        return NULL;
    }

    // Read magic number:
    //retval_fgets = fgets(buf[0], BUFSIZE, fp);
    fgets(buf[0], BUFSIZE, fp);

    // Read width and height:
    do {
        //retval_fgets = fgets(buf[0], BUFSIZE, fp);
        fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');

    //retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
    sscanf(buf[0], "%s %s", buf[1], buf[2]);

    width  = atoi(buf[1]);
    height = atoi(buf[2]);

    // Read maxval:
    do {
        //retval_fgets = fgets(buf[0], BUFSIZE, fp);
        fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');

    // Read image data:
    rawData = new unsigned char[width * height * 3];
    read = fread(rawData, width * height * 3, 1, fp);
    fclose(fp);

    if(read != 1) {
        std::cerr << "error parsing ppm file, incomplete data" << std::endl;
        delete[] rawData;
        width = 0;
        height = 0;
        return NULL;
    }

    return rawData;
}


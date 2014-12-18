#include <iostream>

#include <stdlib.h>
#include <cmath>

#include "window.h"
#include "matrix4.h"
#include "globals.h"
#include "timer.h"

#include <GL/glut.h>

extern float p_camera[3];
extern float l_camera[3];
extern float p_light[3];
extern float l_light[3];
extern GLuint fboId;
extern GLuint depthTextureId;
extern GLuint shadowMapUniform;

int GWindow::width  = 512;   // set window width in pixels here
int GWindow::height = 512;   // set window height in pixels here
Timer GWindow::timer_ = Timer();

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void GWindow::idle_callback()
{
    //if(!Globals::pause) {
        //Globals::focus->update(timer_.get_ticks());
    //}

    //std::cerr << "FPS: " << 1 / (double) timer_.get_ticks() * 1000 << std::endl;
    //timer_.start();


    p_light[0] = 30.0 * std::cos(glutGet(GLUT_ELAPSED_TIME)/1000.0);
    p_light[2] = 30.0 * std::sin(glutGet(GLUT_ELAPSED_TIME)/1000.0);

    display_callback();         // call display routine to show the object

}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void GWindow::reshape_callback(int w, int h)
{
    std::cerr << "GWindow::reshape_callback called" << std::endl;
    width = w;
    height = h;
    glViewport(0, 0, w, h);  // set new viewport size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, width/height,10,40000);
    //gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
    glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
    glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void GWindow::display_callback()
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers

    // Draw current object
    //Matrix4 matrix = Matrix4();
    //matrix.identity();


    glEnable(GL_CULL_FACE);


    // Shadow Mapping

    //First step: Render from the light POV to a FBO, story depth values only
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboId); //Rendering offscreen

    //Using the fixed pipeline to render to the depthbuffer
    glUseProgramObjectARB(0);

    // Clear previous frame values
    glClear(GL_DEPTH_BUFFER_BIT);

    // Disable color rendering, we only want to write to the Z-Buffer
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    setupMatrices(p_light[0],p_light[1],p_light[2],l_light[0],l_light[1],l_light[2]);

    // Culling switching, rendering only backface, this is done to avoid self-shadowing
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    drawObjects();

    // Draw objects
    //Globals::focus->display();
    //Globals::floor->display();

    //Save modelview/projection matrice into texture7, also add a biais
    setTextureMatrix();

    // Now rendering from the camera POV, using the FBO to generate shadows
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    //Enabling color write (previously disabled for light POV z-buffer rendering)
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    // Clear previous frame values
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Using the shadow shader
    //glUseProgramObjectARB(shadowShaderId);
    Globals::shadow_shader->bind();
    glUniform1iARB(shadowMapUniform,7);
    glActiveTextureARB(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D,depthTextureId);

    setupMatrices(p_camera[0],p_camera[1],p_camera[2],l_camera[0],l_camera[1],l_camera[2]);


    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);

    drawObjects();


    /*
    glUseProgramObjectARB(0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2,width/2,-height/2,height/2,1,20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4f(1,1,1,1);
    glActiveTextureARB(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,depthTextureId);
    glEnable(GL_TEXTURE_2D);
    glTranslated(0,0,-1);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);glVertex3f(0,0,0);
    glTexCoord2d(1,0);glVertex3f(width/2,0,0);
    glTexCoord2d(1,1);glVertex3f(width/2,height/2,0);
    glTexCoord2d(0,1);glVertex3f(0,height/2,0);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    */



    //Globals::focus->display(Globals::camera.matrix());
    //Globals::focus->display();
    //Globals::floor->display();


    //Globals::skybox->display();
    //Globals::light1->display();

    //glFlush();  
    glutSwapBuffers();
}



void GWindow::setTextureMatrix(void)
{
    static double modelView[16];
    static double projection[16];

    // This is matrix transform every coordinate x,y,z
    // x = x* 0.5 + 0.5
    // y = y* 0.5 + 0.5
    // z = z* 0.5 + 0.5
    // Moving from unit cube [-1,1] to [0,1]
    const GLdouble bias[16] = {
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0};

    // Grab modelview and transformation matrices
    glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);


    glMatrixMode(GL_TEXTURE);
    glActiveTextureARB(GL_TEXTURE7);

    glLoadIdentity();
    glLoadMatrixd(bias);

    // concatating all matrice into one.
    glMultMatrixd (projection);
    glMultMatrixd (modelView);

    // Go back to normal matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void GWindow::drawObjects(void)
{
    // Ground
    glColor4f(0.3f,0.3f,0.3f,1);
    glBegin(GL_QUADS);
    glVertex3f(-35,2,-35);
    glVertex3f(-35,2, 15);
    glVertex3f( 15,2, 15);
    glVertex3f( 15,2,-35);
    glEnd();

    glColor4f(0.9f,0.9f,0.9f,1);

    // Instead of calling glTranslatef, we need a custom function that also maintain the light matrix
    startTranslate(0,4,-16);
    glutSolidCube(4);
    endTranslate();

    startTranslate(0,4,-5);
    glutSolidCube(4);
    endTranslate();


}

// During translation, we also have to maintain the GL_TEXTURE8, used in the shadow shader
// to determine if a vertex is in the shadow.
void GWindow::startTranslate(float x,float y,float z)
{
    glPushMatrix();
    glTranslatef(x,y,z);

    glMatrixMode(GL_TEXTURE);
    glActiveTextureARB(GL_TEXTURE7);
    glPushMatrix();
    glTranslatef(x,y,z);
}

void GWindow::endTranslate()
{
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void GWindow::setupMatrices(float position_x, float position_y, float position_z, float lookAt_x, float lookAt_y, float lookAt_z)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(60, width/height, 1.0, 1000.0);
    gluPerspective(45,width/height,10,40000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position_x, position_y, position_z, lookAt_x, lookAt_y, lookAt_z, 0, 1, 0);
}


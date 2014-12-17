#include "bezier_patch.h"
#include <math.h>
#include "vector3.h"
#include "globals.h"

#include <GL/glut.h>

static const float MAX_ANGLE = M_PI / 2.0;

BezierPatch::BezierPatch()
{

}

BezierPatch::BezierPatch(GLfloat points[4][4][3])
{
	time = 0.0f;
	inc = 0.005f;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 3; ++k) {
				cp[i][j][k] = points[i][j][k];
			}
		}
	}
	// calc indices
	for (int i = 0; i < detail; ++i) {
		float u = (float)i / (detail - 1);
		for (int j = 0; j < detail; ++j) {
			float v = (float)j / (detail - 1);
			indices[i][j] = calculate(u, v);
			normals[i][j] = calculate_normal(v, (float)(j + 1) / (detail - 1));
		}
	}
    shader_ = new Shader("shader/reflection.vert", "shader/reflection.frag", true);
}

/*
BezierPatch::BezierPatch(Vector3 * v, int x, int y)
{
	time = 0.0f;

	inc = 0.005f;
    for (int i = 0; i < 16; i++){
        cp[i] = v[i];
    }

    //x_ = x;
    //y_ = y;
    setup();

    use_shader_ = false;
    shader_ = new Shader("shader/reflection.vert", "shader/reflection.frag");
}
*/


BezierPatch::~BezierPatch()
{
	// clear indices and normals
	for (int i = 0; i < detail; ++i) {
		for (int j = 0; j < detail; ++j) {
			delete[] indices[i][j];
			delete[] normals[i][j];
		}
	}
	delete[] indices;
	delete[] normals;
}

void BezierPatch::set_cp(GLfloat points[4][4][3])
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 3; ++k) {
				cp[i][j][k] = points[i][j][k];
			}
		}
	}
	// calc indices
	for (int i = 0; i < detail; ++i) {
		float u = (float)i / (detail - 1);
		for (int j = 0; j < detail; ++j) {
			float v = (float)j / (detail - 1);
			if (indices[i][j] != NULL) delete indices[i][j];
			indices[i][j] = calculate(u, v);
			if (normals[i][j] != NULL) delete normals[i][j];
			normals[i][j] = calculate_normal(v, (float)(j + 1) / (detail - 1));
		}
	}
}

GLfloat* BezierPatch::Bez(float t, GLfloat *p0, GLfloat *p1, GLfloat *p2, GLfloat *p3)
{
	GLfloat *p = new GLfloat[3];
	float it = (1.0f - t);

	float b0 = t*t*t;
	float b1 = 3 * t*t*it;
	float b2 = 3 * t*it*it;
	float b3 = it * it * it;

	Vector3 v0, v1, v2, v3;
	v0 = Vector3(p0[0], p0[1], p0[2]);
	v1 = Vector3(p1[0], p1[1], p1[2]);
	v2 = Vector3(p2[0], p2[1], p2[2]);
	v3 = Vector3(p3[0], p3[1], p3[2]);

	Vector3 v;

	v = v0*b0 + v1*b1 + v2*b2 + v3*b3;

	p[0] = v.x();
	p[1] = v.y();
	p[2] = v.z();

	return p;
}

GLfloat* BezierPatch::calculate_normal(float t1, float t2)
{

	GLfloat* q[4];

	q[0] = Bez(t1, cp[0][0], cp[0][1], cp[0][2], cp[0][3]);
	q[1] = Bez(t1, cp[1][0], cp[1][1], cp[1][2], cp[1][3]);
	q[2] = Bez(t1, cp[2][0], cp[2][1], cp[2][2], cp[2][3]);
	q[3] = Bez(t1, cp[3][0], cp[3][1], cp[3][2], cp[3][3]);


	float delta = 0.00001f;
	GLfloat* r[4];

	r[0] = Bez(t1 + delta, cp[0][0], cp[0][1], cp[0][2], cp[0][3]);
	r[1] = Bez(t1 + delta, cp[1][0], cp[1][1], cp[1][2], cp[1][3]);
	r[2] = Bez(t1 + delta, cp[2][0], cp[2][1], cp[2][2], cp[2][3]);
	r[3] = Bez(t1 + delta, cp[3][0], cp[3][1], cp[3][2], cp[3][3]);

	GLfloat* u0 = Bez(t2, q[0], q[1], q[2], q[3]);
	GLfloat* u1 = Bez(t2 + delta, q[0], q[1], q[2], q[3]);

	
	GLfloat tanu[3];

	for (int i = 0; i < 3; ++i) {
		tanu[i] = u1[i] - u0[i];
	}

	GLfloat* v0 = calculate_v(t2, r);

	GLfloat tanv[3];
	for (int i = 0; i < 3; ++i) {
		tanv[i] = v0[i] - u0[i];
	}
	// normalize tanu
	float lengthu = sqrtf(tanu[0] * tanu[0] + tanu[1] * tanu[1] + tanu[2] * tanu[2]);
	for (int i = 0; i < 3; ++i) {
		tanu[i] /= lengthu;
	}
	// normalize tanv
	float lengthv = sqrtf(tanv[0] * tanv[0] + tanv[1] * tanv[1] + tanv[2] * tanv[2]);
	for (int i = 0; i < 3; ++i) {
		tanv[i] /= lengthv;
	}

	// clean up
	for (int i = 0; i < 3; ++i) {
		delete[] q[i];
		delete[] r[i];
	}
	delete[] u0;
	delete[] u1;

	// tanu X tanv
	GLfloat *normal = new GLfloat[3];
	normal[0] = tanu[1] * tanv[2] - tanu[2] * tanv[1];
	normal[1] = tanu[2] * tanv[0] - tanu[0] * tanv[2];
	normal[2] = tanu[0] * tanv[1] - tanu[1] * tanv[0];

	return normal;
}


GLfloat* BezierPatch::calculate_u(float t, int row)
{
	GLfloat *p = new GLfloat[3];
	float it = 1.0f - t;

	// blending function
	float b0 = t*t*t;
	float b1 = 3 * t*t*it;
	float b2 = 3 * t*it*it;
	float b3 = it * it * it;

	// x
	p[0] = b0 * cp[row][0][0] + b1*cp[row][1][0] + b2*cp[row][2][0] + b3*cp[row][3][0];
	// y
	p[1] = b0 * cp[row][0][1] + b1*cp[row][1][1] + b2*cp[row][2][1] + b3*cp[row][3][1];
	// z
	p[2] = b0 * cp[row][0][2] + b1*cp[row][1][2] + b2*cp[row][2][2] + b3*cp[row][3][2];

	return p;
}

GLfloat* BezierPatch::calculate_v(float t, GLfloat** pts)
{
	GLfloat *p = new GLfloat[3];

	float it = 1.0f - t;

	// blending function
	float b0 = t*t*t;
	float b1 = 3 * t*t*it;
	float b2 = 3 * t*it*it;
	float b3 = it * it * it;

	// x
	p[0] = b0*pts[0][0] + b1*pts[1][0] + b2*pts[2][0] + b3*pts[3][0];
	// y
	p[1] = b0*pts[0][1] + b1*pts[1][1] + b2*pts[2][1] + b3*pts[3][1];
	// z
	p[2] = b0*pts[0][2] + b1*pts[1][2] + b2*pts[2][2] + b3*pts[3][2];

	return p;
}

GLfloat* BezierPatch::calculate(float u, float v)
{
	GLfloat *temp[4];// = GLfloat*[4];

	temp[0] = calculate_u(u, 0);
	temp[1] = calculate_u(u, 1);
	temp[2] = calculate_u(u, 2);
	temp[3] = calculate_u(u, 3);

	return calculate_v(v, temp);
}


void BezierPatch::display()
{

    glBindTexture(GL_TEXTURE_CUBE_MAP, Globals::skybox->getSkybox(0));

   // material_.enable();
    shader_->bind();

    glColor3f(0.43, 0.83, 1.0);	
	glBegin(GL_QUADS);
	for (int i = 0; i < detail - 1; ++i) {

		for (int j = 0; j < detail - 1; ++j) {	

			glNormal3fv(normals[i][j]);
			glVertex3fv(indices[i][j]);
			glNormal3fv(normals[i][j+1]);
			glVertex3fv(indices[i][j+1]);
			glNormal3fv(normals[i + 1][j + 1]);
			glVertex3fv(indices[i + 1][j + 1]);
			glNormal3fv(normals[i+1][j]);
			glVertex3fv(indices[i+1][j]);
			
		}
	}
	glEnd();
    shader_->unbind();
}

void BezierPatch::update2()
{
	time += inc;

	GLfloat cp_new[4][4][3];
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			for(int k = 0; k < 3; ++k) {				
				cp_new[i][j][k] = cp[i][j][k];
			}
			if(i == 1) {
				cp_new[i][j][1] = sin(sqrtf((cp[i][j][0]) * (cp[i][j][0]) + (cp[i][j][2]) * (cp[i][j][2])) *  time) * 4 - 10;
			}
			if(i == 2) {
                cp_new[i][j][1] = cos(sqrtf((cp[i][j][0]) * (cp[i][j][0]) + (cp[i][j][2]) * (cp[i][j][2])) *  time) * 4 - 10;
			}
		}
	}
	set_cp(cp_new);
}




void BezierPatch::update(int ticks)
{
    sineWave(0.2, ticks/1000);
}

void BezierPatch::sineWave(double h, double t)
{
    for (int i = 0; i < 16; i++){
        double x = cp[i].x();
        double z = cp[i].z();
        double d = std::sqrt(x * x + z * z);
        double y = h * sin(d * t * M_PI / 2);
        //double y = sin(d * t * M_PI / 2);
        cp[i].set_y(y);
    }

}




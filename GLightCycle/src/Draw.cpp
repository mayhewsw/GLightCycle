/*
 * Draw.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: kimsj
 */

#include <vector>
#include <cmath>
#include <iostream>
#include "Shader.h"
#include "Draw.h"
#include <cstdlib>

using namespace std;

// Set the name of the vertex and fragment shaders here
const char *vShader = "shaders/gaussian.vert";
const char *fShader1 = "shaders/gaussianHoriz.frag";
const char *fShader2 = "shaders/gaussianVert.frag";

static GLint horizBlur = 0;
static GLint vertBlur = 0;


void initUniformParameters() {
	glUniform1i(glGetUniformLocation(horizBlur, "texSize"), glowSize);
	glUniform1i(glGetUniformLocation(vertBlur, "texSize"), glowSize);
}


int windowWidth = 800;
int windowHeight = 800;

GLuint groundTexture, glowTexture;

void init() {
	int r_bits =8, g_bits = 8, b_bits = 8, a_bits=8;
	int depth_bits = 16;
	int stencil_bits = 0;

	glfwOpenWindow(windowWidth, windowHeight,
					r_bits, g_bits, b_bits, a_bits,
					depth_bits, stencil_bits, GLFW_WINDOW);

	// Move the cursor to the center of the screen and hide it
	glfwSetMousePos(windowWidth / 2, windowHeight / 2);
	glfwDisable(GLFW_MOUSE_CURSOR);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);

	GLfloat light0_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	/* set up ambient, diffuse, and specular components for light 0 */
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	generateGround();
	glowTexture = EmptyTexture();

	shaderInit();

	initShader(vShader, fShader1, &horizBlur);
	glUseProgram(horizBlur);
	initUniformParameters();

	glUseProgram(0);

	initShader(vShader, fShader2, &vertBlur);
	glUseProgram(vertBlur);
	initUniformParameters();

	glUseProgram(0);
}

void generateGround() {
	GLbyte *data, *p;
	int texSize = 32;

	data = (GLbyte *)malloc(texSize * texSize * 4);

	int i, j;
	p = data;
	for (i=0; i<texSize; i++) {
		for (j=0; j<texSize; j++) {
			if (i==0 || i == (texSize-1) || j==0 || j == (texSize-1)) {
				p[0] = 0;
				p[1] = 255;
				p[2] = 255;
				p[3] = 255;
			} else {
				p[0] = 0;
				p[1] = 0;
				p[2] = 0;
				p[3] = 0;
			}
			p+=4;
		}
	}

	glGenTextures(1, &groundTexture);
	glBindTexture(GL_TEXTURE_2D, groundTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texSize, texSize, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	free(data);
}

void drawWorld(World *state, bool Glow) {
	int viewports[4][4];

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (state->getNumPlayers() == 1) {
		viewports[0][0] = 0;
		viewports[0][1] = 0;
		viewports[0][2] = windowWidth;
		viewports[0][3] = windowHeight;

		gluPerspective(60.0, (float)(windowWidth)/windowHeight, 0.1, 200);
	} else if (state->getNumPlayers() == 2) {
		viewports[0][0] = 0;
		viewports[0][1] = windowHeight/2;
		viewports[0][2] = windowWidth;
		viewports[0][3] = windowHeight/2;

		viewports[1][0] = 0;
		viewports[1][1] = 0;
		viewports[1][2] = windowWidth;
		viewports[1][3] = windowHeight/2;

		gluPerspective(60.0, (float)(windowWidth)/(windowHeight/2), 0.1, 200);
	} else if (state->getNumPlayers() == 3) {
		viewports[0][0] = 0;
		viewports[0][1] = windowHeight/2;
		viewports[0][2] = windowWidth/2;
		viewports[0][3] = windowHeight/2;

		viewports[1][0] = windowWidth/2;
		viewports[1][1] = windowHeight/2;
		viewports[1][2] = windowWidth/2;
		viewports[1][3] = windowHeight/2;

		viewports[2][0] = 0;
		viewports[2][1] = 0;
		viewports[2][2] = windowWidth;
		viewports[2][3] = windowHeight/2;

		gluPerspective(60.0, (float)(windowWidth)/windowHeight, 0.1, 200);
	} else {
		viewports[0][0] = 0;
		viewports[0][1] = windowHeight/2;
		viewports[0][2] = windowWidth/2;
		viewports[0][3] = windowHeight/2;

		viewports[1][0] = windowWidth/2;
		viewports[1][1] = windowHeight/2;
		viewports[1][2] = windowWidth/2;
		viewports[1][3] = windowHeight/2;

		viewports[2][0] = 0;
		viewports[2][1] = 0;
		viewports[2][2] = windowWidth/2;
		viewports[2][3] = windowHeight/2;

		viewports[3][0] = windowWidth/2;
		viewports[3][1] = 0;
		viewports[3][2] = windowWidth/2;
		viewports[3][3] = windowHeight/2;

		gluPerspective(60.0, (float)(windowWidth)/windowHeight, 0.1, 200);
	}
	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int p;

	for (p=0; p<state->getNumPlayers(); p++) {
	    if (state->getNumPlayers() == 3) {
			if (p==2) {
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(60.0, (float)(windowWidth)/(windowHeight/2), 0.1, 200);
				glMatrixMode(GL_MODELVIEW);
			}
	    }
	    Cycle player = state->getCycles()[p];
	    if (player.getExplosionTime() == 0) {
	    	continue;
	    }

	    // Calculate the camera position
	    GLfloat camera_pos[3] = { player.getPos().x - 6 * cos(player.getDirection()
								  * DEG_TO_RAD), player.getPos().y - 6
				      * sin(player.getDirection() * DEG_TO_RAD), 3.0 };

	    // Calculate the camera's direction
	    GLfloat camera_dir[3] = {
		player.getPos().x + cos(player.getDirection() * DEG_TO_RAD), player.getPos().y
		+ sin(player.getDirection() * DEG_TO_RAD), 0.0 };


	    glViewport(viewports[p][0], viewports[p][1],
		       viewports[p][2], viewports[p][3]);

	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();

	    gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2],
		      camera_dir[0], camera_dir[1], camera_dir[2],
		      0, 0, 1);


	    int i;
	    GLfloat light0_position[4] = { state->width/2, state->height/2, 10.0, 0.0 };

	    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	    glEnable(GL_TEXTURE_2D);
	    glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, groundTexture);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);

			glTexCoord2f(0.0, state->height);
			glVertex3f(0.0, state->height, 0.0);

			glTexCoord2f(state->width, state->height);
			glVertex3f(state->width, state->height, 0.0);

			glTexCoord2f(state->width, 0.0);
			glVertex3f(state->width, 0.0, 0.0);
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);

		for (i=0; i<state->getNumPlayers(); i++) {
			drawTrail(&(state->getTrails())[i]);
			drawCycle(&(state->getCycles())[i]);
			if (state->getCycles()[i].getIsDead()) {
				drawExplosion(&(state->getCycles())[i]);
				continue;
			}
		}
	}
}

void drawTrail(Trail *t) {
	GLfloat trail_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat trail_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat trail_shininess = 0.0;
	float r=0.1,g=0.1,b=0.1,a=1.0;

	if (t->getID() == 0) {
		r = 1.0;
	} else if (t->getID() == 1) {
		g = 1.0;
	} else if (t->getID() == 2) {
		b = 1.0;
	} else {
		r = 1.0;
		g = 1.0;
	}

	GLfloat trail_ambient[] = { r, g, b, a };
	GLfloat trail_emissive[] = { r, g, b, a };

	GLfloat trail_height = 0.5;

	glMaterialfv(GL_FRONT, GL_SPECULAR, trail_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, trail_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, trail_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, trail_emissive);
	glMaterialf(GL_FRONT, GL_SHININESS, trail_shininess);

	std::vector<Coords> *points = t->getPoints();

	int i;

	for(i=1; i<(int)points->size(); i++) {
		glBegin(GL_LINE_LOOP);
		{
			glLineWidth(3.0);
			glVertex3f((*points)[i-1].x, (*points)[i-1].y, 0.0);
			glVertex3f((*points)[i].x, (*points)[i].y, 0.0);
			glVertex3f((*points)[i].x, (*points)[i].y, trail_height);
			glVertex3f((*points)[i-1].x, (*points)[i-1].y, trail_height);
		}
		glEnd();
	}
}

void drawCycle(Cycle *c) {
	//cout << c->getExplosionTime() << endl;

	GLUquadricObj *sphere;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);

	GLfloat cycle_specular[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat cycle_shininess = 128.0;
	float r=0.1,g=0.1,b=0.1,a=0.0;

	if (c->getID() == 0) {
		r = 1.0;
	} else if (c->getID() == 1) {
		g = 1.0;
	} else if (c->getID() == 2) {
		b = 1.0;
	} else {
		r = 1.0;
		g = 1.0;
	}

	GLfloat cycle_ambient[] = { r, g, b, a };
	GLfloat cycle_diffuse[] = { r, g, b, a };

	glMaterialfv(GL_FRONT, GL_SPECULAR, cycle_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, cycle_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cycle_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, cycle_shininess);

	if (c->getIsDead()) {
		return;
	}

	glPushMatrix();
	glTranslated(c->getPos().x, c->getPos().y, 0.5);
	gluSphere(sphere, 0.5, 15, 15);
	glPopMatrix();
}

void drawExplosion(Cycle *c){
    int et = c->getExplosionTime();

    // if the explosion hasn't happened yet
    if (et == INITIAL_EXPLOSION_TIME){
	Coords cCoords = c->getPos();
	c->initExplosion(cCoords.x, cCoords.y, cCoords.z);
    }

    //    cout << "ET: " << et << endl;

    if(et <= 0){
	return;
    }

    // draw particles going nuts
    glPushMatrix ();

    glDisable (GL_LIGHTING);
    glDisable (GL_DEPTH_TEST);

    glBegin (GL_POINTS);

    int i;
    for (i = 0; i < NUM_PARTICLES; i++){
	glColor3fv (c->getParticles()[i].color);
	glVertex3fv (c->getParticles()[i].position);
    }

    glEnd ();

    glPopMatrix ();

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_DEPTH_TEST);

    glNormal3f (0.0, 0.0, 1.0);

    for (i = 0; i < NUM_DEBRIS; i++){
	glColor3fv (c->getDebris()[i].color);

	glPushMatrix ();

	glTranslatef (c->getDebris()[i].position[0],
		      c->getDebris()[i].position[1],
		      c->getDebris()[i].position[2]);

	glRotatef (c->getDebris()[i].orientation[0], 1.0, 0.0, 0.0);
	glRotatef (c->getDebris()[i].orientation[1], 0.0, 1.0, 0.0);
	glRotatef (c->getDebris()[i].orientation[2], 0.0, 0.0, 1.0);

	glScalef (c->getDebris()[i].scale[0],
		  c->getDebris()[i].scale[1],
		  c->getDebris()[i].scale[2]);

	glBegin (GL_TRIANGLES);
	glVertex3f (0.0, 0.5, 0.0);
	glVertex3f (-0.25, 0.0, 0.0);
	glVertex3f (0.25, 0.0, 0.0);
	glEnd ();

	glPopMatrix ();
    }

    c->updateExplosionDetails();
}

static void toOrtho() {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
}

static void toPerspective() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void RenderToTexture() {
	glBindTexture(GL_TEXTURE_2D, glowTexture);

	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, glowSize, glowSize, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void drawTexture(GLint tex) {
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, tex);

	toOrtho();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 1);
		glVertex2f(0, 0);

		glTexCoord2f(0, 0);
		glVertex2f(0, windowHeight);

		glTexCoord2f(1, 0);
		glVertex2f(windowWidth, windowHeight);

		glTexCoord2f(1, 1);
		glVertex2f(windowWidth, 0);
	}
	glEnd();

	toPerspective();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawItem(WorldItem *) {

}

void render(World *state) {
	int tempWidth = windowWidth;
	int tempHeight = windowHeight;

	windowWidth = glowSize;
	windowHeight = glowSize;

	drawWorld(state, true);
	RenderToTexture();

	glViewport(0, 0, glowSize, glowSize);
	glUseProgram(horizBlur);
	drawTexture(glowTexture);
	RenderToTexture();

	glUseProgram(vertBlur);
	drawTexture(glowTexture);
	RenderToTexture();

	windowWidth = tempWidth;
	windowHeight = tempHeight;

	glUseProgram(0);
	drawWorld(state, false);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glViewport(0, 0, windowWidth, windowHeight);
	drawTexture(glowTexture);
	glDisable(GL_BLEND);

	glfwSwapBuffers();
}

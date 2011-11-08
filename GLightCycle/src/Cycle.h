/*
 * Cycle.h
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#ifndef CYCLE_H_
#define CYCLE_H_
#include "Coords.h"

// Some of the ideas and code for the explosion effect was taken from
// http://www.student.nada.kth.se/~nv91-gta/OpenGL/examples/explosion.html

typedef struct particleData
{
  float   position[3];
  float   speed[3];
  float   color[3];
} particleData;

/* A piece of debris */

typedef struct debrisData
{
  float   position[3];
  float   speed[3];
  float   orientation[3];        /* Rotation angles around x, y, and z axes */
  float   orientationSpeed[3];
  float   color[3];
  float   scale[3];
} debrisData;

#define NUM_PARTICLES 1000
#define NUM_DEBRIS 70

#define INITIAL_EXPLOSION_TIME 500


class Cycle {
	Coords pos, lastPos;
	float direction;
	int ID;
	float speed;
	int leftKey, rightKey;
	bool isDead;
	int explosionTime;
	particleData particles[NUM_PARTICLES];
	debrisData   debris[NUM_DEBRIS]; 

	void newSpeed(float[]);

public:
	Cycle();
	Cycle(Coords, float, int, int, int);
	virtual ~Cycle();
	Coords getPos();
	void setPos(Coords);
	float getDirection();
	void setDirection(float);
	int getID();
	float getSpeed();
	void setSpeed(float);
	int getLeftKey();
	int getRightKey();
	bool getIsDead();
	void setToDead();
	int getExplosionTime();
	void updateExplosionDetails();
	
	particleData *getParticles();
	debrisData *getDebris();
	
	void initExplosion(int, int, int);

};

#endif /* CYCLE_H_ */

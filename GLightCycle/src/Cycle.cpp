/*
 * Cycle.cpp
 *
 * Represents a player
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#include "Coords.h"
#include <cmath>
#include <stdlib.h>
#include "Cycle.h"
#include <iostream>
using namespace std;

#define SPEED 0.25

Cycle::Cycle() {

}

Cycle::Cycle(Coords start, float dir, int color, int left, int right) {
	pos = start;
	lastPos = start;
	direction = dir;
	ID = color;
	speed = SPEED;
	leftKey = left;
	rightKey = right;
	isDead = 0;
	explosionTime = INITIAL_EXPLOSION_TIME;
	itemEffect = false;
}

Cycle::~Cycle() {
}


Coords Cycle::getPos() {
	return pos;
}

Coords Cycle::getLastPos() {

	return lastPos;
}


void Cycle::setPos(Coords newPos) {
	lastPos = pos;
	pos = newPos;
}

float Cycle::getDirection() {
	return direction;
}

void Cycle::setDirection(float newDir) {
	direction = newDir;
}

int Cycle::getID() {
	return ID;
}

float Cycle::getSpeed() {
	return speed;
}

void Cycle::setSpeed(float newSpeed) {
	speed = newSpeed;
}

int Cycle::getLeftKey() {
	return leftKey;
}

int Cycle::getRightKey() {
	return rightKey;
}

bool Cycle::getIsDead() {
	return isDead;
}

void Cycle::setToDead() {
	isDead = true;
}

particleData *Cycle::getParticles(){
    return particles;
}

debrisData *Cycle::getDebris(){
    return debris;
}

int Cycle::getExplosionTime(){
    return explosionTime;
}

/**
 * This method initializes all of the particles that
 * shoot off when a player collides with something
 */
void Cycle::initExplosion(float x, float y, float z){
    int i;
    for (i = 0; i < NUM_PARTICLES; i++){
      particles[i].position[0] = x;
      particles[i].position[1] = y;
      particles[i].position[2] = z;

      particles[i].color[0] = 1.0;
      particles[i].color[1] = 1.0;
      particles[i].color[2] = 0.5;

      newSpeed (particles[i].speed);
    }

    for (i = 0; i < NUM_DEBRIS; i++){
      debris[i].position[0] = x;
      debris[i].position[1] = y;
      debris[i].position[2] = z;

      debris[i].orientation[0] = x;
      debris[i].orientation[1] = y;
      debris[i].orientation[2] = z;

      debris[i].color[0] = 0.7;
      debris[i].color[1] = 0.7;
      debris[i].color[2] = 0.7;

      debris[i].scale[0] = (2.0 * 
			    ((float) rand ()) / ((float) RAND_MAX)) - 1.0;
      debris[i].scale[1] = (2.0 * 
			    ((float) rand ()) / ((float) RAND_MAX)) - 1.0;
      debris[i].scale[2] = (2.0 * 
			    ((float) rand ()) / ((float) RAND_MAX)) - 1.0;

      newSpeed (debris[i].speed);
      newSpeed (debris[i].orientationSpeed);
    }

}

/**
 * This gives the particle a randomly generated speed
 */
void Cycle::newSpeed (float dest[3])
{
    float    x;
    float    y;
    float    z;
    float    len;
    
    x = (2.0 * ((float) rand ()) / ((float) RAND_MAX)) - 1.0;
    y = (2.0 * ((float) rand ()) / ((float) RAND_MAX)) - 1.0;
    z = (2.0 * ((float) rand ()) / ((float) RAND_MAX)) - 1.0;
    
    len = sqrt (x * x + y * y + z * z);
    
    if (len){
	x = x / len;
	y = y / len;
	z = z / len;
    }
    
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
}

void Cycle::updateExplosionDetails(){
    int i;
    for (i = 0; i < NUM_PARTICLES; i++){
	particles[i].position[0] += particles[i].speed[0] * 0.2;
	particles[i].position[1] += particles[i].speed[1] * 0.2;
	particles[i].position[2] += particles[i].speed[2] * 0.2;
	
	particles[i].color[0] -= 1.0 / 500.0;
	if (particles[i].color[0] < 0.0){
	    particles[i].color[0] = 0.0;
	}
	
	particles[i].color[1] -= 1.0 / 100.0;
	if (particles[i].color[1] < 0.0){
	    particles[i].color[1] = 0.0;
	}
	
	particles[i].color[2] -= 1.0 / 50.0;
	if (particles[i].color[2] < 0.0){
	    particles[i].color[2] = 0.0;
	}
    }

    
    for (i = 0; i < NUM_DEBRIS; i++){
	debris[i].position[0] += debris[i].speed[0] * 0.1;
	debris[i].position[1] += debris[i].speed[1] * 0.1;
	debris[i].position[2] += debris[i].speed[2] * 0.1;
	
	debris[i].orientation[0] += debris[i].orientationSpeed[0] * 10;
	debris[i].orientation[1] += debris[i].orientationSpeed[1] * 10;
	debris[i].orientation[2] += debris[i].orientationSpeed[2] * 10;
    }

    // decrement explosion time
    explosionTime -= 1;
}

/**
 * Called when the player picks up an item, this starts
 * the timer for when the item wears off
 */
void Cycle::setItemEffect() {
	itemEffect = true;
	seconds = time(NULL);
}

/**
 * Checks if enough time has passed. If so,
 * reset the player's speed
 */
void Cycle::timer() {
	if (!itemEffect) return;

	int t = (int) difftime(time(NULL), seconds);

	if (t > ITEM_EFFECT_TIME) {
		itemEffect = false;
		speed = SPEED;
	}
}

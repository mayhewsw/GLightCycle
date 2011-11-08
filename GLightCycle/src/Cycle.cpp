/*
 * Cycle.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#include "Coords.h"
#include "Cycle.h"
using namespace std;

Cycle::Cycle() {

}

Cycle::Cycle(Coords start, float dir, int color, int left, int right) {
	// TODO Auto-generated constructor stub
	pos = start;
	lastPos = start;
	direction = dir;
	ID = color;
	speed = 0.05;
	leftKey = left;
	rightKey = right;
	isDead = 0;
	explosionTime = 500;
}

Cycle::~Cycle() {
	// TODO Auto-generated destructor stub
}

Coords Cycle::getPos() {
	return pos;
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

void Cycle::setExplosionTime(int t){
    explosionTime = t;
}

int Cycle::getExplosionTime(){
    return explosionTime;
}

particleData *getParticles(){
    return particles;
}

debrisData *getDebris(){
    return debris;
}

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

Cycle::Cycle(Coords start, float dir, int color) {
	// TODO Auto-generated constructor stub
	pos = start;
	lastPos = start;
	direction = dir;
	ID = color;
	speed = 0.1;
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

float Cycle::getSpeed() {
	return speed;
}

void Cycle::setSpeed(float newSpeed) {
	speed = newSpeed;
}

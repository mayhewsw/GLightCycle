/*
 * World.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#include <math.h>
#include "Cycle.h"
#include "Trail.h"
#include "World.h"
#include "Coords.h"
#include "Draw.h"
#include <iostream>
#include <GL/glfw.h>
using namespace std;

#define DEG_TO_RAD M_PI/180.0

World::World(int w, int h, int n) {
    width = w;
    height = h;
    numPlayers = n;
    livePlayers = numPlayers;
    trails = new Trail[numPlayers];
    cycles = new Cycle[numPlayers];
    int keys[8] = { 'A', 'D', 'J', 'L', GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_KP_4, GLFW_KEY_KP_6 };

    float dir;
    float startX, startY;
    for (int i = 0; i < n; i++) {
        dir = i*90.0;
        startX = w/2 + cos(dir*DEG_TO_RAD);
        startY = h/2 + sin(dir*DEG_TO_RAD);
        cycles[i] = Cycle(Coords(startX, startY), dir, i, keys[i*2], keys[i*2+1]);
        trails[i] = Trail(Coords(startX, startY), i);
    }
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::move() {
	int i;
	Cycle currentCycle;
	Trail currentTrail;
	Coords newPos;

	for (i=0; i<numPlayers; i++) {
		if (cycles[i].getIsDead()) {
			continue;
		}
		currentCycle = cycles[i];
		currentTrail = trails[i];
		turn(&currentCycle);

		float newX = currentCycle.getPos().x + currentCycle.getSpeed() * cos(currentCycle.getDirection() * DEG_TO_RAD);
		float newY = currentCycle.getPos().y + currentCycle.getSpeed() * sin(currentCycle.getDirection() * DEG_TO_RAD);

		newPos = Coords(newX, newY);

		currentCycle.setPos(newPos);

		currentTrail.addPoint(newPos);

		trails[i] = currentTrail;

		if (!isValidMove(currentCycle)) {
			kill(&currentCycle);
		}

		cycles[i] = currentCycle;

	}
	trailDetect();
}

void World::turn(Cycle *c) {
	float turnSensitivity = 4.0;

	if (glfwGetKey(c->getLeftKey())) {
		c->setDirection(c->getDirection() + turnSensitivity);
	}
	if (glfwGetKey(c->getRightKey())) {
		c->setDirection(c->getDirection() - turnSensitivity);
	}

	if (c->getDirection() > 360) {
		c->setDirection(c->getDirection() - 360);
	} else if (c->getDirection() < -360) {
		c->setDirection(c->getDirection() + 360);
	}
}

bool World::isValidMove(Cycle c) {
	Coords pos = c.getPos();

	if (pos.x < 0 || pos.x > width || pos.y < 0 || pos.y > height) {
		return false;
	}

	return true;
}


void World::trailDetect(){

	unsigned int i, j;
	for (j = 0; j < numPlayers; j++) {
		if (!cycles[j].getIsDead()) {
			unsigned int f = trails[j].getPoints()->size() - 1;
			for (i = 1; i < f; i = i+1) {
				if (!cycles[0].getIsDead() && intersection( cycles[0].getLastPos(), cycles[0].getPos(),
						trails[j].points[i], trails[j].points[i + 1])) {
					kill(&cycles[0]);
				}
				if (numPlayers > 1 && !cycles[1].getIsDead() && intersection(
						cycles[1].getLastPos(), cycles[1].getPos(),
						trails[j].points[i], trails[j].points[i + 1])) {
					kill(&cycles[1]);
				}
				if (numPlayers > 2 && !cycles[2].getIsDead() && intersection(
						cycles[2].getLastPos(), cycles[2].getPos(),
						trails[j].points[i], trails[j].points[i + 1])) {
					kill(&cycles[2]);
				}
				if (numPlayers > 3 && !cycles[3].getIsDead() && intersection(
						cycles[3].getLastPos(), cycles[3].getPos(),
						trails[j].points[i], trails[j].points[i + 1])) {
					kill(&cycles[3]);
				}

			}
		}
	}


}

bool World::intersection(Coords a, Coords b, Coords c, Coords d) {
//	float ax = a.x;
//	float ay = a.y;
//	float bx = b.x;
//	float by = b.y;
//	float cx = c.x;
//	float cy = c.y;
//	float dx = d.x;
//	float dy = d.y;
//	if(ax == cx && ay == cy)
//		return false;
//	if(bx == dx && by == dy)
//		return false;

//	float denom = ((ay - by) * (cx - dx) - (ax - bx) * (cy - dy));
//	float i = (((ax * by) - (bx * ay) + (bx * cy) - (cx * by) + (cx * ay) - (ax
//			* cy))) / denom;
//	float j = ((cx * dy) - (dx * cy) + (dx * ay) - (ax * dy) + (ax * cy) - (cx
//			* ay)) / denom;
//	if (i > .01 && i < .99 && j > .01 && j < .99 )
//		return true;
//	return false;

	float u1 = b.x - a.x;
	float u2 = b.y - a.y;
	float v1 = d.x - c.x;
	float v2 = d.y - c.y;
	float w1 = c.x - a.x;
	float w2 = c.y - a.y;

//	if (((w1*v2)-(w2*v1)) == 0) {
//		return true;
//	}

	float denom = (v1*u2) - (v2*u1);

	float s = ((v2*w1)-(v1*w2))/denom;
	float t = ((u1*w2)-(u2*w1))/(-denom);

	if (s > .01 && s < .99 && t > .01 && t < .99) {
		return true;
	}

	return false;
}

void World::kill(Cycle *c) {
	int ID = c->getID();
	cout << trails[ID].getPoints()->size() << endl;
	trails[ID].clear();
	cout << trails[ID].getPoints()->size() << endl;
	c->setToDead();
	livePlayers--;
}

Cycle *World::getCycles() {
	return cycles;
}

std::vector<WorldItem> World::getItems() {
	return items;
}

int World::getNumPlayers() {
	return numPlayers;
}

Trail *World::getTrails() {
	return trails;
}

int World::getWidth()
{
	return width;
}

void World::setNumPlayers(int np)
{
	numPlayers = np;
}

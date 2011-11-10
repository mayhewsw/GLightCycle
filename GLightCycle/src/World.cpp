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
	items = new WorldItem[3];// magic # of items
	int keys[8] = { 'A', 'D', 'J', 'L', GLFW_KEY_LEFT, GLFW_KEY_RIGHT,
			GLFW_KEY_KP_4, GLFW_KEY_KP_6 };
	float dir;
    float startX, startY;
    for (int i = 0; i < n; i++) {
        dir = i*90.0;
        startX = w/2 + cos(dir*DEG_TO_RAD);
        startY = h/2 + sin(dir*DEG_TO_RAD);
        cycles[i] = Cycle(Coords(startX, startY), dir, i, keys[i*2], keys[i*2+1]);
        trails[i] = Trail(Coords(startX, startY), i);
    }

	for (int i = 0; i < 3; i++) {// 3 is magic
		items[i] = WorldItem();
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

	for (i = 0; i < numPlayers; i++) {
		if (cycles[i].getIsDead()) {
			continue;
		}
		Cycle c = cycles[i];
		c.timer();
		cycles[i] = c;

		currentCycle = cycles[i];
		currentTrail = trails[i];
		turn(&currentCycle);

		float newX = currentCycle.getPos().x + currentCycle.getSpeed() * cos(
				currentCycle.getDirection() * DEG_TO_RAD);
		float newY = currentCycle.getPos().y + currentCycle.getSpeed() * sin(
				currentCycle.getDirection() * DEG_TO_RAD);

		newPos = Coords(newX, newY);

		currentCycle.setPos(newPos);

		currentTrail.addPoint(newPos);

		trails[i] = currentTrail;

		if (!isValidMove(currentCycle)) {
			kill(&currentCycle);
		}
		hitItem(&currentCycle);

		cycles[i] = currentCycle;

	}
	trailDetect();
}

void World::turn(Cycle *c) {
	float turnSensitivity = 6.0;

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

void World::hitItem(Cycle *c) {
	Coords pos = c->getPos();
	WorldItem wi;

	for (int i = 0; i < 3; i++) {

		if (distance(items[i].getPos(), pos) <= CYCLE_RADIUS + ITEM_RADIUS) {
			//action
			if (items[i].getID() == 0)
				kill(c);
			else if (items[i].getID() == 1)
				c->setSpeed(0.1);
			else if (items[i].getID() == 2)
				c->setSpeed(0.5);

			// Item will be inactive for a few seconds
			items[i] = WorldItem();

			c->setItemEffect();
		}
		wi = items[i];
		wi.timer();
		items[i] = wi;

	}
}

double World::distance(Coords a, Coords b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));

}

void World::trailDetect() {

	unsigned int i, j;
	for (j = 0; j < numPlayers; j++) {
		if (!cycles[j].getIsDead()) {
			unsigned int f = trails[j].getPoints()->size() - 1;
			for (i = 1; i < f; i = i + 1) {
				if (!cycles[0].getIsDead() && intersection(
						cycles[0].getLastPos(), cycles[0].getPos(),
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
	float ax = a.x;
	float ay = a.y;
	float bx = b.x;
	float by = b.y;
	float cx = c.x;
	float cy = c.y;
	float dx = d.x;
	float dy = d.y;
	float denom = ((ay - by) * (cx - dx) - (ax - bx) * (cy - dy));
	float i = (((ax * by) - (bx * ay) + (bx * cy) - (cx * by) + (cx * ay) - (ax
			* cy))) / denom;
	float j = ((cx * dy) - (dx * cy) + (dx * ay) - (ax * dy) + (ax * cy) - (cx
			* ay)) / denom;
	if (i > .01 && i < .99 && j > .01 && j < .99)
		return true;
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

WorldItem *World::getItems(){
	return items;
}

int World::getNumPlayers() {
	return numPlayers;
}

Trail *World::getTrails() {
	return trails;
}

int World::getWidth() {
	return width;
}

void World::setNumPlayers(int np) {
	numPlayers = np;
}

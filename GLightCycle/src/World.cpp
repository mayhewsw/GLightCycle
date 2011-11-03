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
#include <iostream>
#include <GL/glfw.h>
using namespace std;

#define DEG_TO_RAD M_PI/180.0

World::World(int w, int h, int n) {
    width = w;
    height = h;
    numPlayers = n;
    trails = new Trail[numPlayers];
    cycles = new Cycle[numPlayers];
    int keys[8] = { 'A', 'D', 'J', 'L', GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_KP_4, GLFW_KEY_KP_6 };

    float dir;
    for (int i = 0; i < n; i++) {
        trails[i] = Trail(Coords(w/2, h/2), i);

        dir = i*90.0;
        cycles[i] = Cycle(Coords(w/2 + cos(dir*DEG_TO_RAD), h/2 + sin(dir*DEG_TO_RAD)), dir, i, keys[i*2], keys[i*2+1]);
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
		currentCycle = cycles[i];
		currentTrail = trails[i];
		turn(&currentCycle);

		float newX = currentCycle.getPos().x + currentCycle.getSpeed() * cos(currentCycle.getDirection() * DEG_TO_RAD);
		float newY = currentCycle.getPos().y + currentCycle.getSpeed() * sin(currentCycle.getDirection() * DEG_TO_RAD);

		newPos = Coords(newX, newY);

		currentCycle.setPos(newPos);

		currentTrail.addPoint(newPos);

		cycles[i] = currentCycle;
		trails[i] = currentTrail;
	}
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

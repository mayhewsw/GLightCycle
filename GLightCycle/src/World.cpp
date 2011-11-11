/*
 * World.cpp
 *
 * Represents the world as a whole.
 * Also acts as a "manager" of sorts, handling
 * cycle movement, item generation, and collision
 * detection
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

/**
 * Initializes the world state
 */
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

/**
 * A bit of a misnomer, as this method does more
 * than just "move"
 *
 * This updates the state of the game, which includes
 * adding trails, updating player positions, checking if an
 * item was hit, and checking for collisions
 */
void World::move() {
	int i;
	Cycle currentCycle;
	Trail currentTrail;
	Coords newPos;

	// Iterate through each player
	for (i = 0; i < numPlayers; i++) {
		// If the player is dead, no need to
		// update his/her state
		if (cycles[i].getIsDead()) {
			continue;
		}

		currentCycle = cycles[i];
		currentTrail = trails[i];

		// Update any item effects
		currentCycle.timer();

		// Turn the player
		turn(&currentCycle);

		// Move him/her forward
		float newX = currentCycle.getPos().x + currentCycle.getSpeed() * cos(
				currentCycle.getDirection() * DEG_TO_RAD);
		float newY = currentCycle.getPos().y + currentCycle.getSpeed() * sin(
				currentCycle.getDirection() * DEG_TO_RAD);

		// Set the player's new position
		newPos = Coords(newX, newY);
		currentCycle.setPos(newPos);

		// Add the point to the trail
		currentTrail.addPoint(newPos);

		// Apply the change to the trail
		trails[i] = currentTrail;

		// Check if the player is still in the bounds
		// of the world
		if (!isValidMove(currentCycle)) {
			kill(&currentCycle);
		}

		// Check if the player has collected an
		// item
		hitItem(&currentCycle);

		// Apply the change to the cycle
		cycles[i] = currentCycle;

	}

	// Check for collisions. This is called outside the loop
	// because it's a one-pass check
	trailDetect();
}

/**
 * Adjust the player's direction if he/she is pressing
 * the appropriate turn key
 */
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

/**
 * Checks if the player is within the bounds of the room
 */
bool World::isValidMove(Cycle c) {
	Coords pos = c.getPos();

	if (pos.x < 0 || pos.x > width || pos.y < 0 || pos.y > height) {
		return false;
	}

	return true;
}

/**
 * Checks if an item is hit
 */
void World::hitItem(Cycle *c) {
	Coords pos = c->getPos();
	WorldItem wi;

	for (int i = 0; i < 3; i++) {

		if (distance(items[i].getPos(), pos) <= CYCLE_RADIUS + ITEM_RADIUS) {
			//action
			if (items[i].getID() == 0)
				kill(c);
			else if (items[i].getID() == 1)
				c->setSpeed(c->getSpeed()*0.5);
			else if (items[i].getID() == 2)
				c->setSpeed(c->getSpeed()*1.5);

			// Item will be inactive for a few seconds
			items[i] = WorldItem();

			// Apply the effect to the player
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

/**
 * Checks if any player has crossed a trail
 */
void World::trailDetect() {

	unsigned int i;
	int j;
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

/**
 * Kills off the player
 */
void World::kill(Cycle *c) {
	int ID = c->getID();
	trails[ID].clear();
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

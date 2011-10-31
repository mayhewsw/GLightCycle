/*
 * World.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#include "Cycle.h"
#include "Trail.h"
#include "World.h"
#include "Coords.h"
#include <iostream>
using namespace std;

World::World(int w, int h, int n) {
    width = w;
    height = h;
    numPlayers = n;
    trails = new Trail[numPlayers];
    cycles = new Cycle[numPlayers];
    for (int i = 0; i < n; i++) {
        trails[i] = Trail(Coords(w/2, h/2), i);
        cycles[i] = Cycle(Coords(w/2, h/2), i*90.0, i);
    }
}

World::~World() {
	// TODO Auto-generated destructor stub
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

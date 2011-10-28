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
using namespace std;

World::World(int w, int h, int n) {
	// TODO Auto-generated constructor stub
	width = w;
	height = h;
	numPlayers = n;

	Coords startingPos[numPlayers] = { Coords::Coords(0, 0), Coords::Coords(0, h),
						  Coords::Coords(w, h), Coords::Coords(w, 0) };

	int i;
	for (i=0; i<numPlayers; i++) {
		cycles[i] = Cycle::Cycle(startingPos[0], 0, i);
	}
}

World::~World() {
	// TODO Auto-generated destructor stub
}

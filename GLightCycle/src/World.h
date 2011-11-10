/*
 * World.h
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */


#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include "Trail.h"
#include "Cycle.h"
#include "WorldItem.h"

#define BOARD_WIDTH 50
#define BOARD_HEIGHT 50
#define CYCLE_RADIUS 0.5
#define ITEM_RADIUS 0.4

class World {
	int numPlayers;
	Trail *trails;
	Cycle *cycles;
	WorldItem *items;
public:
	int width, height;
	World(int, int, int); //width, height, numPlayers
	virtual ~World();
	void move();
	void turn(Cycle *);
	bool isValidMove(Cycle);
	void kill(Cycle *);
	Cycle *getCycles();
	int getNumPlayers();
	Trail *getTrails();
	int getWidth();
	void setNumPlayers(int);
	bool intersection(Coords, Coords, Coords, Coords);
	void trailDetect();
	void hitItem(Cycle *);
	double distance (Coords, Coords);
	WorldItem *getItems();
};

#endif /* WORLD_H_ */

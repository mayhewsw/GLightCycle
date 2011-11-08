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

class World {
	int numPlayers;
	Trail *trails;
	Cycle *cycles;
	std::vector<WorldItem> items;
public:
	int width, height;
	World(int, int, int); //width, height, numPlayers
	virtual ~World();
	void move();
	void turn(Cycle *);
	bool isValidMove(Cycle);
	void kill(Cycle *);
	Cycle *getCycles();
	std::vector<WorldItem> getItems();
	int getNumPlayers();
	Trail *getTrails();
	int getWidth();
	void setNumPlayers(int);
};

#endif /* WORLD_H_ */

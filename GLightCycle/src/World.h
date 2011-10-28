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
	static int numPlayers;
	int width, height;
	Trail trails[];
	Cycle cycles[];
	std::vector<WorldItem> items;
public:
	World(int, int, int); //width, height, numPlayers
	virtual ~World();
};

#endif /* WORLD_H_ */

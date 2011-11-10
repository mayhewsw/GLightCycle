/*
 * WorldItem.cpp
 *
 *  Created on: Oct 28, 2011
 *      Author: kimsj
 */

#include "WorldItem.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

WorldItem::WorldItem() {
	ID = 1;//rand() % 3; //generate random [0,2]
	loc = Coords(rand() % 50, rand() % 50);
	active = false;
	seconds = time(NULL);

}

WorldItem::~WorldItem() {
	// TODO Auto-generated destructor stub
}

void WorldItem::timer() {
	int t = (int) difftime(time(NULL), seconds);

	if (t > SPAWN) {
		active = true;
	}

}

bool WorldItem::getActive(){
	return active;
}

int WorldItem::getID() {
	return ID;
}

Coords WorldItem::getPos(){
	return loc;
}

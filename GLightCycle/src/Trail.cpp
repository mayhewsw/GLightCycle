/*
 * Trail.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#include <vector>
#include "Coords.h"
#include "Trail.h"

Trail::Trail() {

}

Trail::Trail(Coords start, int newID) {
	// TODO Auto-generated constructor stub
	points.push_back(start);
	ID = newID;
}

Trail::~Trail() {
	// TODO Auto-generated destructor stub
}

void Trail::addPoint(Coords point) {
	points.push_back(point);
}

std::vector<Coords> *Trail::getPoints() {
	return &points;
}

void Trail::setPoints(std::vector<Coords> newPoints) {
	points = newPoints;
}

void Trail::clear() {
	points.clear();
}

int Trail::getID() {
	return ID;
}

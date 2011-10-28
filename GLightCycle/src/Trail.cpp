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

Trail::Trail(Coords start) {
	// TODO Auto-generated constructor stub
	points.push_back(start);
}

Trail::~Trail() {
	// TODO Auto-generated destructor stub
}

void Trail::addPoint(Coords point) {
	points.push_back(point);
}

std::vector<Coords> Trail::getPoints() {
	return points;
}

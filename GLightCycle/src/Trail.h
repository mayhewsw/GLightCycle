/*
 * Trail.h
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#ifndef TRAIL_H_
#define TRAIL_H_

#include "Coords.h"
#include <vector>

class Trail {
	std::vector<Coords> points;
	int ID;
public:
	Trail();
	Trail(Coords);
	virtual ~Trail();
	void addPoint(Coords);
	std::vector<Coords> getPoints();
};

#endif /* TRAIL_H_ */

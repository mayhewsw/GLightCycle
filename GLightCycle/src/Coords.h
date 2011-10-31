/*
 * Coords.h
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#ifndef COORDS_H_
#define COORDS_H_

class Coords {
public:
	float x, y, z;
	Coords();
	Coords(float, float);
	Coords(float, float, float);
	virtual ~Coords();
};

#endif /* COORDS_H_ */

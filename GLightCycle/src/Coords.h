/*
 * Coords.h
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#ifndef COORDS_H_
#define COORDS_H_

class Coords {
	float x, y, z;
public:
	Coords();
	Coords(float, float);
	Coords(float, float, float);
	virtual ~Coords();
	float getX(void);
	float getY(void);
	float getZ(void);
	void set (float, float);
	void set(float, float, float);
};

#endif /* COORDS_H_ */

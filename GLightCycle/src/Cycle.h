/*
 * Cycle.h
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#ifndef CYCLE_H_
#define CYCLE_H_

class Cycle {
	Coords pos, lastPos;
	float direction;
	int ID;
	float speed;
public:
	Cycle(Coords, float, int);
	virtual ~Cycle();
	Coords getPos();
	void setPos(Coords);
	float getDirection();
	void setDirection(float);
	float getSpeed();
	void setSpeed(float);
};

#endif /* CYCLE_H_ */

/*
 * Cycle.h
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#ifndef CYCLE_H_
#define CYCLE_H_
#include "Coords.h"

class Cycle {
	Coords pos, lastPos;
	float direction;
	int ID;
	float speed;
	int leftKey, rightKey;
	bool isDead;
	int explosionTime;
public:
	Cycle();
	Cycle(Coords, float, int, int, int);
	virtual ~Cycle();
	Coords getPos();
	void setPos(Coords);
	float getDirection();
	void setDirection(float);
	int getID();
	float getSpeed();
	void setSpeed(float);
	int getLeftKey();
	int getRightKey();
	bool getIsDead();
	void setToDead();
	void setExplosionTime(int);
	int getExplosionTime();
};

#endif /* CYCLE_H_ */

/*
 * WorldItem.h
 *
 *  Created on: Oct 28, 2011
 *      Author: kimsj
 */

#ifndef WORLDITEM_H_
#define WORLDITEM_H_
#include <time.h>
#include "Coords.h"
#define SPAWN 5
class WorldItem {
	int ID;
	bool active;
	Coords loc;
	time_t seconds;

public:
	WorldItem();
	virtual ~WorldItem();
	int getID();
	Coords getPos();
	bool getActive();
	void timer();
};

#endif /* WORLDITEM_H_ */

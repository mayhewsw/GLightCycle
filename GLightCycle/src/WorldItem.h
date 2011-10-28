/*
 * WorldItem.h
 *
 *  Created on: Oct 28, 2011
 *      Author: kimsj
 */

#ifndef WORLDITEM_H_
#define WORLDITEM_H_

#include "Coords.h"

class WorldItem {
	int ID;
	Coords loc;
public:
	WorldItem();
	virtual ~WorldItem();
};

#endif /* WORLDITEM_H_ */

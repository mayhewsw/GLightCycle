/*
 * World.h
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */


#ifndef WORLD_H_
#define WORLD_H_

class World {
	int width, height;
	Trail trails[];

public:
	World();
	virtual ~World();
};

#endif /* WORLD_H_ */

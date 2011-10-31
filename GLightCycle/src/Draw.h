/*
 * Draw.h
 *
 *  Created on: Oct 30, 2011
 *      Author: kimsj
 */

#ifndef DRAW_H_
#define DRAW_H_

#include "World.h"

void init();
void drawWorld(World *);
void drawPlane();
void drawTrail(Trail *);
void drawCycle(Cycle *);
void drawItem(WorldItem *);

#endif /* DRAW_H_ */

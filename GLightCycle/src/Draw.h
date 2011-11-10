/*
 * Draw.h
 *
 *  Created on: Oct 30, 2011
 *      Author: kimsj
 */

#ifndef DRAW_H_
#define DRAW_H_

#include "World.h"
#include <GL/glfw.h>

#define DEG_TO_RAD M_PI/180.0

void init();
void generateGround();
void drawWorld(World *);
void drawPlane();
void drawTrail(Trail *);
void drawCycle(Cycle *);
void drawItem(WorldItem *);
void drawExplosion(Cycle *);
void drawItem(WorldItem *);
void render(World *);

#endif /* DRAW_H_ */

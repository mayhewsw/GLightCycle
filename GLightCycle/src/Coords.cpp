/*
 * Coords.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#include "Coords.h"

Coords::Coords() {
	x = 0;
	y = 0;
	z = 0;
}

Coords::Coords(float a, float b) {
	x = a;
	y = b;
	z = 0;
}

Coords::Coords(float a, float b, float c) {
	// TODO Auto-generated constructor stub
	x = a;
	y = b;
	z = c;
}

Coords::~Coords() {
	// TODO Auto-generated destructor stub
}

float Coords::getX() {
	return x;
}

float Coords::getY() {
	return y;
}

float Coords::getZ() {
	return z;
}

void Coords::set(float a, float b) {
	x = a;
	y = b;
}

void Coords::set(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

//============================================================================
// Name        : GLightCycle.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "World.h"
#include "Draw.h"
#include <glfw.h>
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	World game = World(50, 50, 4);

	/* GLFW initialization */
	glfwInit();
	init();

	int running = GL_TRUE;

	while (running) {
		drawWorld(&game);
		game.move();
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}

	glfwTerminate();

	return 0;
}

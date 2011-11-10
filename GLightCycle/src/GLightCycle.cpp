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
#include <GL/glfw.h>
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	unsigned int numplay = 3;

	cout << "Enter number of players : " << endl;
//	cin >> numplay;


	World game = World(50, 50, numplay);

	/* GLFW initialization */
	glfwInit();
	init();

	int running = GL_TRUE;
	long counter = 100;

	for (long i = 0; i < counter; i++){
		drawWorld(&game);
	}

	while (running) {
		drawWorld(&game);
		game.move();
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}

	glfwTerminate();

	return 0;
}

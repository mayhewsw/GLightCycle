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
	unsigned int numplay = 2;

	// Prompt the user for the number of players
	cout << "Enter number of players : " << endl;
	cin >> numplay;


	srand(time(NULL));//initialize random seed

	// initialize the world
	World game = World(BOARD_WIDTH, BOARD_HEIGHT, numplay);

	/* GLFW initialization */
	glfwInit();
	init();

	int running = GL_TRUE;
	long counter = 100;

	// Stall the game for a short while to let the players get ready
	for (long i = 0; i < counter; i++){
		render(&game);
	}

	while (running) {
		render(&game);
		game.move();
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}

	glfwTerminate();

	return 0;
}

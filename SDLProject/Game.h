#pragma once
#ifndef Game_h
#define Game_h

#include <iostream>
#include <vector>

#include "SDL.h"
#include "Board.h"


class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	void handleEvents();

	void render();

	void update();

	void clean();

	bool running() { return isRunning; }

	void stopGame();

private:
	int width, height;

	bool isRunning;
	Board* board;
	SDL_Window* window;
	SDL_Renderer* renderer;
};


#endif Game_h
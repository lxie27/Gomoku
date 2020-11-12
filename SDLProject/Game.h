#pragma once
#ifndef Game_h
#define Game_h

#include "SDL.h"
#include <iostream>
#include <vector>

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	void handleEvents();

	void update();

	void render();

	void clean();

	void initQuad(std::vector<std::vector<int>>& quad);

	void updateQuad(std::vector<std::vector<int>>& quad);

	void renderQuad(SDL_Renderer* renderer, std::vector<std::vector<int>> quad);

	bool running() { return isRunning; }

private:
	int width, height;

	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<std::vector<int>> quad;

};


#endif Game_h
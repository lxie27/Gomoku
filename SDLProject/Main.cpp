#include "SDL.h"
#include <iostream>
#include "Game.h"

#undef main

int GAME_WIDTH = 750;
int GAME_HEIGHT = 750;

Game* game = nullptr;

int main(int argc, char* argv)
{
	game = new Game();
	game->init("Gomoku with AI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, false);

	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}
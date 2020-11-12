#include "SDL.h"
#include <iostream>
#include "Game.h"

#undef main

Game* game = nullptr;


int main(int argc, char* argv)
{
	game = new Game();
	game->init("Quad Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}
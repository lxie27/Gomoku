#include "Game.h"
#include <cstdlib>
#include <ctime>

Game::Game()
{
	board = new Board;
	ai = new AI;
}

Game::~Game()
{}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		this->width = width;
		this->height = height;

		std::cout << "SDL Subsystems Initialized..." << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			std::cout << "SDL Window Created..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 101, 67, 33, 255);
			std::cout << "SDL Renderer Created..." << std::endl;
		}

		board->renderBoard(renderer);
		isRunning = true;

	}
	else
	{
		isRunning = false;
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			if (board->attemptAdd(event.motion.x, event.motion.y))
			{
				board->switchPlayers();
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Game::update()
{
	if (board->getWinner() != 0)
	{
		stopGame();
	}

	if (board->getCurrentPlayer() == WHITE)
	{
		std::pair<int, int> attemptedAIMove = ai->makeMove(board->boardState);
		board->attemptAdd(attemptedAIMove.first, attemptedAIMove.second);
		board->switchPlayers();
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 128, 90, 70, 255);
	board->renderBoard(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game has been cleaned..." << std::endl;
}

void Game::stopGame()
{
	isRunning = false;
}

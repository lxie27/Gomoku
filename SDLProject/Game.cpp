#include "Game.h"
#include <cstdlib>
#include <ctime>

Game::Game()
{}

Game::~Game()
{}

//	Initializes the quad's starting points
void Game::initQuad(std::vector<std::vector<int>>& quad)
{
	std::vector<int> tl{ 100, 100 };
	std::vector<int> tr{ 200, 100 };
	std::vector<int> br{ 200, 200 };
	std::vector<int> bl{ 100, 200 };

	quad.push_back(tl);
	quad.push_back(tr);
	quad.push_back(br);
	quad.push_back(bl);
}

//	TODO: Randomly changes quad's points
void Game::updateQuad(std::vector<std::vector<int>>& quad)
{
	std::srand(std::time(nullptr));

	int midX = quad[1][0] - quad[0][0] / 2;
	int midY = quad[2][1] - quad[1][1] / 2;

	for (int i = 0; i <= 3; i++)
	{
		quad[i][0] += (std::rand() % 3) - 1;
		quad[i][1] += (std::rand() % 3) - 1;

		//	Clip if trying to leave boundaries of window
		if (quad[i][0] < 0)
		{
			quad[i][0] = 0;
		}
		else if (quad[i][0] > this->width)
		{
			quad[i][0] = this->width;
		}

		if (quad[i][1] < 0)
		{
			quad[i][1] = 0;
		}
		else if (quad[i][1] > this->height)
		{
			quad[i][1] = this->height;
		}
	}



	SDL_Delay(2);
}
//	Renders a quad
void Game::renderQuad(SDL_Renderer* renderer, std::vector<std::vector<int>> quad)
{
	//Top left point to top right point
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(renderer, quad[0][0], quad[0][1], quad[1][0], quad[1][1]);

	//Top right point to bottom right point
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, quad[1][0], quad[1][1], quad[2][0], quad[2][1]);

	//Bottom right point to bottom left point
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(renderer, quad[2][0], quad[2][1], quad[3][0], quad[3][1]);

	//Bottom left point to top left point
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, quad[3][0], quad[3][1], quad[0][0], quad[0][1]);
}

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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "SDL Renderer Created..." << std::endl;
		}

		//Initializing the quad's position and size
		initQuad(quad);

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

	default:
		break;
	}
}

void Game::update()
{
	updateQuad(quad);
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//TODO: add moving rectangle here to render
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	renderQuad(renderer, quad);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game has been cleaned..." << std::endl;
}

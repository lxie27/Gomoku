#include "Board.h"
#include <iostream>

int GAME_W = 750;
int GAME_H = 750;

Board::Board()
{
}

Board::~Board()
{
}

void Board::switchPlayers()
{
	currentPlayer = !currentPlayer;
}

bool Board::getCurrentPlayer()
{
	return currentPlayer;
}

/**
 * Puts a piece on the board based on column/row indices.
 * @param {colIndex} - left-right index (column)
 * @param {rowIndex} - up-down index (row)
 * @param {piece} - the color piece to place
 */
void Board::putPiece(int colIndex, int rowIndex)
{
	if (colIndex < 0 || colIndex >= 15)
	{
		std::cout << "Incorrect colIndex" << std::endl;
		return;
	}

	if (rowIndex < 0 || rowIndex >= 15)
	{
		std::cout << "Incorrect rowIndex" << std::endl;
		return;
	}
	
	this->boardState[colIndex][rowIndex] = getCurrentPlayer();
}

/** 
 * Adds a piece to the board based on the mouse click's coordinates.
 * @param {mouseX} - x coordinate of left click
 * @param {mouseY} - y coordinate of left click
 */
void Board::addPiece(int mouseX, int mouseY)
{
	int xIndex = GAME_W / mouseX;
	int yIndex = GAME_H / mouseY;
	
	putPiece(xIndex, yIndex);
}

void renderPiece(SDL_Renderer* renderer, bool piece)
{
	if (piece == 1)
	{
		SDL_SetRenderDrawColor(renderer, 255, 250, 250, 255);
	}
}
void Board::renderBoard(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	for (int i = 1; i < 15; i++)
	{
		SDL_RenderDrawLine(renderer, GAME_W / 15 * i, 0, GAME_W / 15 * i, GAME_H);
		SDL_RenderDrawLine(renderer, 0, GAME_H / 15 * i, GAME_W, GAME_H / 15 * i);
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			SDL_Rect rect;
			rect.x = GAME_W / 15 * i + 5;
			rect.y = GAME_H / 15 * j + 5;
			rect.w = GAME_W / 15 - 10;
			rect.h = GAME_H / 15 - 10;

			if (boardState[i][j] == 0)
			{
				SDL_SetRenderDrawColor(renderer, 255, 250, 250, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
			else if (boardState[i][j] == 1)
			{
				SDL_SetRenderDrawColor(renderer, 27, 30, 35, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
	//draws white piece
	//SDL_SetRenderDrawColor(renderer, 252, 252, 252, 255);
}

//	This searches for any 5 of the same piece in a row.
bool Board::winState()
{
	return false;
}
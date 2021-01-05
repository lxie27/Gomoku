#include "Board.h"
#include <iostream>
#include <thread>

int GAME_W = 750;
int GAME_H = 750;

Board::Board()
{
}

Board::~Board()
{
}

Square Board::getWinner()
{
	return winner;
}

void Board::switchPlayers()
{
	if (getCurrentPlayer() == WHITE)
	{
		currentPlayer = BLACK;
	}
	else if (getCurrentPlayer() == BLACK)
	{
		currentPlayer = WHITE;
	}
}

Square Board::getCurrentPlayer()
{
	return currentPlayer;
}

//	Returns if a given column and row is open for placement
bool Board::isOpenSpot(int colIndex, int rowIndex)
{
	if (boardState[colIndex][rowIndex] == EMPTY)
	{
		return true;
	}
	else
	{
		return false;
	}
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
		return;
	}

	if (rowIndex < 0 || rowIndex >= 15)
	{
		return;
	}
	
	boardState[colIndex][rowIndex] = getCurrentPlayer();
}

/**
* This does the check when attempting to add a piece to the board.
 * @param {mouseX} - x coordinate of left click
 * @param {mouseY} - y coordinate of left click
 * @returns - true if attempt is successful
*/
bool Board::attemptAdd(int mouseX, int mouseY)
{
	int xIndex = mouseX / 50;
	int yIndex = mouseY / 50;

	if (isOpenSpot(xIndex, yIndex) == true)
	{
		addPiece(mouseX, mouseY);
		if (informedWinState(xIndex, yIndex, getCurrentPlayer()) == EMPTY)
		{
			switchPlayers();
		}
		else
		{
			winner = getCurrentPlayer();
		}
		return true;
	}
	else
	{
		return false;
	}
}

/** 
 * Adds a piece to the board based on the mouse click's coordinates.
 * @param {mouseX} - x coordinate of left click
 * @param {mouseY} - y coordinate of left click
 */
void Board::addPiece(int mouseX, int mouseY)
{
	int xIndex = mouseX / 50;
	int yIndex = mouseY / 50;

	putPiece(xIndex, yIndex);

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

			if (boardState[i][j] == 1) //WHITE
			{
				SDL_SetRenderDrawColor(renderer, 255, 250, 250, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
			else if (boardState[i][j] == 2) //BLACK
			{
				SDL_SetRenderDrawColor(renderer, 27, 30, 35, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
}

/*	Used for one-directional checking
 * @param {colIndex}	- column index	of the added stone
 * @param {rowIndex}	- row index		of the added stone
 * @param {color}		- color			of the added stone
 * @param {colDelta}	- the direction to check the next horizontal space, should only take -1 or 1
 * @param {rowDelta}	- the direction to check the next vertical space, should only take -1 or 1
 * @param {count}		- counter used to recursively check the same direction for 5 stones in a row
 * @returns				- largest consecutive amount of same-colored pieces
 */
int Board::checkNextSpace(int colIndex, int rowIndex, Square color, int colDelta, int rowDelta, int count)
{
	if (color == BLACK)
	{
		//std::cout << "Checking:" << colIndex << ", " << rowIndex << std::endl;
	}
	// Out of bounds checking
	if (colIndex + colDelta >= 14 || colIndex + colDelta < 0 || 
		rowIndex + rowDelta >= 14 || rowIndex + rowDelta < 0)
	{
		return count;
	}

	// Check the next square for matching color square
	if (boardState[colIndex + colDelta][rowIndex + rowDelta] == color)
	{
		count++;

		if (count >= 5)
		{
			return count;
		}
		// On fail, proceed to next square using index + deltas
		else
		{
			return checkNextSpace(colIndex + colDelta, rowIndex + rowDelta, color, colDelta, rowDelta, count);
		}
	}
	else
	{
		return count;
	}
}

/*	Essentially a wrapper function for bi-directional checking
 * @param {colIndex}	- column index	of the added stone
 * @param {rowIndex}	- row index		of the added stone
 * @param {color}		- color			of the added stone
 * @param {colDelta}	- the direction to check the next horizontal space, should only take -1 or 1
 * @param {rowDelta}	- the direction to check the next vertical space, should only take -1 or 1
 * @returns				- if there are 5-in-a-row from the inputted colIndex, rowIndex
 */
bool Board::checkBothDirections(int colIndex, int rowIndex, Square color, int colDelta, int rowDelta)
{
	if (checkNextSpace(colIndex, rowIndex, color, colDelta, rowDelta, 1)
		+ checkNextSpace(colIndex, rowIndex, color, -colDelta, -rowDelta, 0) >= 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//	This search for any 5 in the same piece in a row when aware of last stone's position and color
Square Board::informedWinState(int colIndex, int rowIndex, Square color)
{
	if (checkBothDirections(colIndex, rowIndex, color, -1, 0)	// left & right
		|| checkBothDirections(colIndex, rowIndex, color, 0, 1)	// down & up
		|| checkBothDirections(colIndex, rowIndex, color, -1, 1)	// leftdown & rightup
		|| checkBothDirections(colIndex, rowIndex, color, 1, 1))	// rightdown & leftup
	{
		return color;
	}

	else
	{
		return EMPTY;
	}
}
#include "AI.h"
#include <iostream>
#include <cstdlib>

AI::AI(){}

AI::~AI(){}

//TODO: the actual algorithm. Currently just finds a random spot and puts a square there.
std::pair<int, int> AI::makeMove(Square boardState[15][15])
{
	int row = 0;
	int col = 0;

	//	Find a spot that isn't occupied, use that spot.
	while (boardState[row][col] != EMPTY)
	{
		row = rand() % 15;
		col = rand() % 15;
	}

	// Convert to mouse coordinates
	// Yeah, I know this is bad code but that's a problem for future Leslie. Sorry future Leslie.
	std::cout << "AI is attempting a move at: " << row << ", " << col << std::endl;
	return std::pair<int, int>(row * 50, col * 50);
}

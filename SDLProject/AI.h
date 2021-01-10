#pragma once
#include <utility>
#include "Board.h"

class AI
{
public:
	AI();
	~AI();

	std::pair<int, int> makeMove(Square boardState[15][15]);
};


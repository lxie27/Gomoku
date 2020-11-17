#pragma once
#include "SDL.h"
#include <vector>

class Board
{
public:
	Board();
	~Board();

	void switchPlayers();
	bool getCurrentPlayer();

	void putPiece(int colIndex, int rowIndex);
	void addPiece(int mouseX, int mouseY);

	void renderBoard(SDL_Renderer* renderer);
	bool winState();

private:
	//	Currrent player's turn, defaults to white
	bool currentPlayer = 0;
	bool boardState[15][15];
};
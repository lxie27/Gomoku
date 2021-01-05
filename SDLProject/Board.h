#pragma once
#include "SDL.h"
#include <vector>

enum Square
{
	EMPTY, WHITE, BLACK
};

class Board
{
public:
	Board();
	~Board();

	Square getWinner();

	void switchPlayers();
	Square getCurrentPlayer();
	bool isOpenSpot(int colIndex, int rowIndex);

	void putPiece(int colIndex, int rowIndex);
	bool attemptAdd(int mouseX, int mouseY);
	void addPiece(int mouseX, int mouseY);

	void renderBoard(SDL_Renderer* renderer);

	int checkNextSpace(int colIndex, int rowIndex, Square color, int colDelta, int rowDelta, int count);
	bool checkBothDirections(int colIndex, int rowIndex, Square color, int colDelta, int rowDelta);
	Square informedWinState(int colIndex, int rowIndex, Square color);

private:
	//	Currrent player's turn, defaults to BLACK
	Square currentPlayer = BLACK;
	Square boardState[15][15] = { EMPTY };
	Square winner = EMPTY;
};
#pragma once

#include "tetrimino.h"
const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 24;


class Well
{
private:
	char board[BOARD_HEIGHT][BOARD_WIDTH];
	int height;
	int width;
	
	//MUTATORS
	void moveRowsDown(int firstRowToMove);

	//ACCESSORS
	bool rowIsFull(int row);

public:

	//CONSTRUCTOR
	Well();

	//ACCESSORS
	void getBoard(char whatBoard[][BOARD_WIDTH]);
	bool tetriminoFit(Tetrimino myTetrimino);
	
	//MUTATORS
	int clearFullRows();
	void addTetriminoToWell(Tetrimino myTetrimino);

	//OTHER
	void boardDump();
	bool topReached();
};


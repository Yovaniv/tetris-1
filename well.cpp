/*
@file		well.cpp
@author		dale crawford
@version	3.0

Implementation of the well class with tetrimino class
*/

#include "well.h"
#include <iostream>
#include <cstdlib>
using namespace std;


/*
******************************************************
				CONSTRUCTORS
******************************************************
*/
// initializes the well to its proper dimensions
//		sets all board squares to ' '
Well::Well()
{
	// initialize height and width to 24 & 8
	int height = BOARD_HEIGHT;
	int width = BOARD_WIDTH;
	
	// each location is a blank space or a char for color
	for (int rows = 0; rows < BOARD_HEIGHT; rows++) {
		for (int columns = 0; columns < BOARD_WIDTH; columns++) {
			board[rows][columns] = ' ';
		}
	}
}



/*
******************************************************
				ACCESSORS
******************************************************
*/


// returns a copy of the board[][] into whatBoard[][]
void Well::getBoard(char whatBoard[][BOARD_WIDTH]) // copies the contents of the well board onto whatBoard[][]
{
	for (int rows = 0; rows < BOARD_HEIGHT; rows++) {
		for (int columns = 0; columns < BOARD_WIDTH; columns++) {
			whatBoard[rows][columns] = board[rows][columns];
		}
	}
}

// returns true if the tetrimino fits on the board as-is
bool Well::tetriminoFit(Tetrimino myTetrimino) 
{ 
	//we need the location of myTetrimino: use getLocation() to store a copy of myTetrimino's location into a local Location
	Location myLoc = myTetrimino.getLocation();

	//we also need the grid of myTetrimino to find where the 1's are
	int myGrid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];
	
	//use getGrid to store a copy of myTetrimino;s grid into a local 4x4 int array
	myTetrimino.getGrid(myGrid);

	//determine where the 1's are in the grid: loop through the grid to check each spot
	for (int tetColIndex = 0; tetColIndex < TETRIMINO_GRID_SIZE; tetColIndex++) 
	{
		for (int tetRowIndex = 0; tetRowIndex < TETRIMINO_GRID_SIZE; tetRowIndex++)
		{	//if we see a 1 determine the location of that 1 on the gameboard
			if (myGrid[tetRowIndex][tetColIndex] == 1) 
			{
				//create variable for translatable board height and row indeces to simplfy logic
				int bHeightIndex = tetRowIndex + myLoc.row;
				int bWidthIndex = tetColIndex + myLoc.col;
				
				// if the bWidthIndex is not negative, we know that it will be to the 
				// right of the left constraint of the board, so we know we only have
				// 2 more constraints to limit out before comparing to gameboard pieces: 
				// bottom() and right
				if (bWidthIndex >= 0) 
				{
					// if the piece is either on or above the board (top doesn't matter)
					// check to see if this a valid spot on the rest of the game board 
					if (bWidthIndex < BOARD_WIDTH && bHeightIndex < BOARD_HEIGHT)
					{

						//if it's a spot on the wall and occupied, it's an invalid location
						//so return false
						if (board[bWidthIndex][bHeightIndex] != ' ' && bHeightIndex >= 0) 
						{
							return false;
						}
					}
				}
			}
		}
	}

	//return true if the function hasn't exited with false
	return true;
}


/*
******************************************************
				MUTATORS
******************************************************
*/

// PRIVATE copies all rows down 1 level starting from firstRowToMove,
//		working back up to the row before the top (as that one 
//		has no meaningful data to move into it) 
void Well::moveRowsDown(int firstRowToMove) 
{
	for (int rowIndex = firstRowToMove; rowIndex > 0; rowIndex--) 
	{
		for (int colIndex = 0; colIndex < BOARD_WIDTH; colIndex++)
		{
			board[rowIndex][colIndex] = board[(rowIndex - 1)][colIndex];
		}
	}
}

// clears the rows that dont have empty spaces and returns the
//		number of rows it cleared
int Well::clearFullRows()
{	// create int numRowsCleared to keep track of how many rows you cleared
	int numRowsCleared = 0;

	// loop through the board starting at the top and check all of your rows
	for (int rowNumber = 0; rowNumber < BOARD_HEIGHT; rowNumber++) {
		// use bool rowIsFull to look for fullRows
		if (rowIsFull(rowNumber)) 
		{
			// if true, use void moveRowsDown()
			moveRowsDown(rowNumber);
			
			// clear the top row
			for (int cIndex = 0; cIndex < BOARD_WIDTH; cIndex++) {
				board[0][cIndex] = ' ';
			}

			// increment the number of rows cleared
			numRowsCleared++;
		}
	}
	// return numRowsCleared
	return numRowsCleared;
}


//adds the tetrimino to the well
void Well::addTetriminoToWell(Tetrimino myTetrimino) {
	if (tetriminoFit(myTetrimino)) {
		Location myLoc = myTetrimino.getLocation();
		int tempGrid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];
		
		// stores an copy of myTetrimino grid on tempGrid
		myTetrimino.getGrid(tempGrid); 
		for (int rIndex = 0; rIndex < TETRIMINO_GRID_SIZE; rIndex++)
			for (int cIndex = 0; cIndex < TETRIMINO_GRID_SIZE; cIndex++) 
			{ 	// basically the above part loops through the tetrimino and we are looking for 1's
				if (tempGrid[rIndex][cIndex] == 1)
				{	//because we know the tetrimino fits we can just copy the color to the board at tet location
					board[(rIndex + myLoc.row)][(cIndex + myLoc.row)] = myTetrimino.getColor();
				}
			}
	}
}
/*
******************************************************
				OTHER FUNCTIONS
******************************************************
*/

// PRIVATE returns true if the row is full
bool Well::rowIsFull(int row)
{	// loop through the row given
	for (int position = 0; position < BOARD_WIDTH; position++){ 
		
		// check each spot check to see if there is a space
		if (board[row][position] == ' ')	
			
			// if there is, return false
			return false;					
	}
	
	// return true once it gets through all positions in the row and none are spaces
	return true;
}

// returns true if there is a piece in the top row of the well
bool Well::topReached()
{	
	for (int position = 0; position < BOARD_WIDTH; position++) {

		// check each spot to see if it's NOT a space
		if (board[0][position] != ' ')
		{
			// if evaluated true, return true because it means a piece is in the top row
			return true;
		}
	}
	// return false if it gets through all positions in the row and all are spaces
	return false;
}

// prints out to the console the contents of the board
void Well::boardDump()
{	// loops through the height
	for (int heightIndex = 0; heightIndex < BOARD_HEIGHT; heightIndex++) {
		// and width of the grid
		for (int widthIndex = 0; widthIndex < BOARD_WIDTH; widthIndex++) {
			// and prints to the console each row chars, separated by comma and space
			cout << board[heightIndex][widthIndex] << ", ";
		}
		// then ends the line before printing the next row
		cout << endl;
	}
}



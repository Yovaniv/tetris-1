/*
@file		tetrimino.cpp
@author		dale crawford
@version	2.0

Implementation of the Tetrimino class with tetrimino.h
*/

#include "tetrimino.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
******************************************************
				SHAPES DEFINITIONS
******************************************************
*/

int square[][TETRIMINO_GRID_SIZE] = {
	{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}
};
int zag[][TETRIMINO_GRID_SIZE] = {
	{0,0,0,0},
	{0,1,1,0},
	{0,0,1,1},
	{0,0,0,0}
};
int revZag[][TETRIMINO_GRID_SIZE] = {
	{0,0,0,0},
	{0,0,1,1},
	{0,1,1,0},
	{0,0,0,0}
};
int rightL[][TETRIMINO_GRID_SIZE] = {
	{0,1,0,0},
	{0,1,0,0},
	{0,1,1,0},
	{0,0,0,0}
};
int leftL[][TETRIMINO_GRID_SIZE] = {
	{0,0,1,0},
	{0,0,1,0},
	{0,1,1,0},
	{0,0,0,0}
};
int straight[][TETRIMINO_GRID_SIZE] = {
	{0,1,0,0},
	{0,1,0,0},
	{0,1,0,0},
	{0,1,0,0}
};
int tripod[][TETRIMINO_GRID_SIZE] = {
	{0,0,0,0},
	{0,1,0,0},
	{0,1,1,0},
	{0,1,0,0}
};

/*
******************************************************
				CONSTRUCTORS
******************************************************
*/

//sets location, type(number 0-6), color of tetrimino and fills in tetrimino grid 
Tetrimino::Tetrimino(int type) {
	srand((int)time(0));
	setLocation(0, 0);
	if (type < 0 || type > 6) { // if the number is invalid, set it to a
		type = (rand() % 6);		// random valid value
	}

	switch (type) {
	case 0: //square
		duplicateGrid(square, grid);
		color = 'k'; //black
		break;
	case 1: //zag
		duplicateGrid(zag, grid);
		color = 'b'; //blue
		break;
	case 2: // reverse zag
		duplicateGrid(revZag, grid);
		color = 'c'; //cyan
		break;
	case 3: // right L
		duplicateGrid(rightL, grid);
		color = 'g'; //green
		break;
	case 4: // left L
		duplicateGrid(leftL, grid);
		color = 'm'; //magenta
		break;
	case 5: // straight piece
		duplicateGrid(straight, grid);
		color = 'r'; //red
		break;
	case 6: // tripod
		duplicateGrid(tripod, grid);
		color = 'y'; //yellow
		break;
	}
}

/*
******************************************************
				ACCESSORS
******************************************************
*/
char Tetrimino::getColor() { // returns the color of the tetrimino object
	return color;
}
Location Tetrimino::getLocation() { // return the location of the Tetrimino
	return location;
}
void Tetrimino::getGrid(int gridOut[][TETRIMINO_GRID_SIZE]) { //copy the value of grid to gridOut
	duplicateGrid(grid, gridOut);
}


void Tetrimino::printGrid(int shape[][TETRIMINO_GRID_SIZE]) {
	for (int x = 0; x < TETRIMINO_GRID_SIZE; x++) {
		for (int y = 0; y < TETRIMINO_GRID_SIZE; y++) {
			cout << shape[x][y] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

/*
******************************************************
				MUTATORS
******************************************************
*/
void Tetrimino::setLocation(Location newLocation) { // modify location.row and location.col
	location.row = newLocation.row;
	location.col = newLocation.col;
}

void Tetrimino::setLocation(int row, int col) { // modify location.row and location.col
	location.row = row;
	location.col = col;
}

void Tetrimino::rotateLeft() {
	//initializes temp array for copying
	int temp[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];

	//copies the array rotated left to the temp array
	for (int rowIndex = 0; rowIndex < TETRIMINO_GRID_SIZE; rowIndex++) {
		int counter = 0;
		for (int col = 3; col >= 0; col--) {
			temp[counter][rowIndex] = grid[rowIndex][col];
			counter++;
		}
	}
	duplicateGrid(temp, grid);
}
void Tetrimino::rotateRight() {
	//initializes temp array for copying
	int temp[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];

	//copies the array rotated right to the temp array
	for (int col = 0; col < TETRIMINO_GRID_SIZE; col++) {
		int counter = 0;
		for (int rowIndex = (TETRIMINO_GRID_SIZE - 1); rowIndex >= 0; rowIndex--) {
			temp[col][counter] = grid[rowIndex][col];
			counter++;
		}
	}
	duplicateGrid(temp, grid);
}

void Tetrimino::moveLeft() {
	location.col--;
}
void Tetrimino::moveRight() {
	location.col++;
}
void Tetrimino::moveDown() {
	location.row++;
}
void Tetrimino::moveUp() {
	location.row--;
}






/*
******************************************************
				OTHER FUNCTIONS
******************************************************
*/
void Tetrimino::dataDump() { // print out the value of grid, color, and location
	printGrid(grid);
	cout << "the grid color is: " << color << endl;
	cout << "the grid location is: (" << location.row << ", " << location.col << ")" << endl;
}

void Tetrimino::duplicateGrid(int gridFrom[][TETRIMINO_GRID_SIZE], int gridTo[][TETRIMINO_GRID_SIZE]) {
	for (int rows = 0; rows < TETRIMINO_GRID_SIZE; rows++) {
		for (int columns = 0; columns < TETRIMINO_GRID_SIZE; columns++) {
			gridTo[rows][columns] = gridFrom[rows][columns];
		}
	}
}











/*
******************************************************
					TESTING
******************************************************
*/

// int main() {
//
// 	return 0;
// }

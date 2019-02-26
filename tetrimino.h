#pragma once

const int TETRIMINO_GRID_SIZE = 4;

struct Location {
	int row; //y-position
	int col; //x-position
};

class Tetrimino {
private:
	int grid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE]; //contains only zeros and ones
	char color;
	Location location;
public:
	//CONSTRUCTORS
	Tetrimino(int type = 7); // valid type values are 0-6

	// ACCESSORS
	char getColor(); // returns the color of the tetrimino object
	Location getLocation(); // return the location of the Tetrimino
	void getGrid(int gridOut[][TETRIMINO_GRID_SIZE]); 	//copies tetrimino grid to gridout
	void printGrid(int shape[][TETRIMINO_GRID_SIZE]); 	//prints tetrimino grid


	
	// MUTATORS
	void setLocation(Location newLocation); // modify location.row and location.col
	void setLocation(int row, int col); // modify location.row and location.col
	void rotateLeft();
	void rotateRight();
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();

	// OTHER HELPER FUNCTIONS
	void dataDump(); // print out the value of grid, color, and location
	void duplicateGrid(int gridFrom[][TETRIMINO_GRID_SIZE], int gridTo[][TETRIMINO_GRID_SIZE]);// copies one grid to another
};

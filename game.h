#pragma once
#include "well.h"

const int LAYOUT_WINDOW_WIDTH = 400;
const int LAYOUT_WINDOW_HEIGHT = 500;
const int LAYOUT_BOARD_TOP = 10;
const int LAYOUT_BOARD_LEFT = 200;
const int BLOCK_SIZE_PIXELS = 20;

using namespace sf;

class Game
{
private: 
	RenderWindow window;
	Well gameWell;
	Tetrimino tetriminoInPlay;


	//CONSTRUCTORS?
	void drawWell(Well myWell, int top, int left, int blockPixSize);
	void drawTetrimino(Tetrimino myTet, int top, int left, int blockPixSize);

	//MUTATORS
	Color convertToSfmlColor(char tetColor);

public:
	//CONSTRUCTOR
	Game();

	//OTHER
	void playGame();



};


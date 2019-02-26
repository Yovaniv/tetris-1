/*
@file		game.cpp
@author		dale crawford
@version	4.0

Implementation of the game class with all other files

this version allows us to draw the well and interact with
the tetrimino in the output window
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "game.h"

using namespace sf;


/*
******************************************************
				PUBLIC-Constructor
******************************************************
*/

Game::Game()
{
	Tetrimino tetriminoInPlay(7);
	window.create(VideoMode(LAYOUT_WINDOW_WIDTH, LAYOUT_WINDOW_HEIGHT),
		"Tetris 2019", Style::Titlebar | Style::Close);
}



/*
******************************************************
				PRIVATE-Mutators
******************************************************
*/


// draws the well on the game console
void Game::drawWell(Well myWell, int top, int left, int blockPixSize)
{
	int wellWidth = blockPixSize * BOARD_WIDTH;
	int wellHeight = blockPixSize * BOARD_HEIGHT;

	// create a rectangle shape in sfml for the well outline
	RectangleShape myOutline;
	myOutline.setSize(Vector2f(wellWidth, wellHeight));
	
	// set outline thickness, outline color, fill color, 
		//     the position in the window
	myOutline.setOutlineThickness(1);
	myOutline.setOutlineColor(Color::Magenta);
	myOutline.setFillColor(Color::White);
	myOutline.setPosition(left, top);
		
	// draw it
	window.draw(myOutline);


	// create a rectangle shape (myBlock) to draw each block in the well
	RectangleShape myBlock;
	myBlock.setSize(Vector2f(blockPixSize, blockPixSize));
	myBlock.setOutlineThickness(1);
	myBlock.setOutlineColor(Color::Black);

	// use getBoard function to get a copy of the board from myWell & store
	//		in a local array
	char localBoard[BOARD_HEIGHT][BOARD_WIDTH];
	//myWell.addTetriminoToWell(tetriminoInPlay); //did this to test borders when i was working on them
	myWell.getBoard(localBoard);

	// create a nested loop to draw the inside of myWell (which you now have a copy of)
	for (int rows = 0; rows < BOARD_HEIGHT; rows++) {
		for (int columns = 0; columns < BOARD_WIDTH; columns++) {
			
			// if the current index is NOT a blank character, draw a rectangle
			if (localBoard[rows][columns] != ' ') {
				
				// use the convertToSmflColor function to set the color of the rectangle
				myBlock.setFillColor(convertToSfmlColor(localBoard[rows][columns]));
				
				// set the position of the rectangle to the correct place in the SFML render window
				int positionX = (blockPixSize * columns) + left;
				int positionY = (blockPixSize * rows) + top;
				myBlock.setPosition(positionX, positionY);
				
				// window.draw(myBlock)
				window.draw(myBlock);
			}
		}
	}		
}


// draws tetriminoInPlay on the gameboard
void Game::drawTetrimino(Tetrimino myTet, int top, int left, int blockPixSize)
{
	// create a rectangle shape (myBlock) to draw each block of the tetrimino
	RectangleShape myBlock;
	myBlock.setSize(Vector2f(blockPixSize-1, blockPixSize-1));
	myBlock.setOutlineThickness(1);
	myBlock.setOutlineColor(Color::Black);
	
	//get a copy of the myTet int grid
	int localGrid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];
	tetriminoInPlay.getGrid(localGrid);

	//create nested loop to search the copy of the grid
	for (int rows = 0; rows < TETRIMINO_GRID_SIZE; rows++) {
		for (int columns = 0; columns < TETRIMINO_GRID_SIZE; columns++) {
			//if the current index == 1
			if (localGrid[rows][columns] == 1) {
				//use the convertToSmflColor(myTet.color) to setFillColor of myBlock
				myBlock.setFillColor(convertToSfmlColor(myTet.getColor()));
				//set the position of the rectangle to the correct place in the smfl render
				int positionX = (blockPixSize * columns) + left + myTet.getLocation().col;
				int positionY = (blockPixSize * rows) + top + myTet.getLocation().row;
				myBlock.setPosition(positionX, positionY);

				// window.draw(myBlock)
				window.draw(myBlock);
			}
			
		}
	}
		
}


// helper function, takes input char color and converts it to color class
Color Game::convertToSfmlColor(char tetColor)
{
	Color myColor;
	switch (tetColor) {
	case 'k':
		myColor = myColor.Black;
		break;
	case 'b':
		myColor = myColor.Blue;
		break;
	case 'c':
		myColor = myColor.Cyan;
		break;
	case 'g':
		myColor = myColor.Green;
		break;
	case 'm':
		myColor = myColor.Magenta;
		break;
	case 'r':
		myColor = myColor.Red;
		break;
	case 'y':
		myColor = myColor.Yellow;
		break;
	}
	return myColor;
}


//other function
void Game::playGame()
{
	while (window.isOpen()) {

		//game loop
		Event Event;
		while (window.pollEvent(Event)) {
			switch (Event.type) 
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				// i realize i couldve done a nested switch but i'm demonstrating
				//		diversity here... or something
				if (Event.key.code == Keyboard::Left) {
					tetriminoInPlay.moveLeft();
					//std::cout << "Moved Left" << std::endl;
					//std::cout << "Tetrimino Location now: (" << tetriminoInPlay.getLocation().row <<
						//", " << tetriminoInPlay.getLocation().col << ")" << std::endl;
				}
				if (Event.key.code == Keyboard::Right) {
					tetriminoInPlay.moveRight();
					//std::cout << "Moved Right" << std::endl;
					//std::cout << "Tetrimino Location now: (" << tetriminoInPlay.getLocation().row <<
						//", " << tetriminoInPlay.getLocation().col << ")" << std::endl;
				}
				if (Event.key.code == Keyboard::Up) {
					tetriminoInPlay.rotateRight();
					//std::cout << "Rotated Right" << std::endl;
				}
				if (Event.key.code == Keyboard::Escape) {
					window.close();
				}
				break;
			case Event::GainedFocus:
				std::cout << "window active" << std::endl;
				break;
			case Event::LostFocus:
				std::cout << "window not active" << std::endl;
				break;
			}
		}
		
		// draw the well
		drawWell(gameWell, LAYOUT_BOARD_TOP, LAYOUT_BOARD_LEFT, BLOCK_SIZE_PIXELS);

		//draw tetrimino
		drawTetrimino(tetriminoInPlay, LAYOUT_BOARD_TOP, LAYOUT_BOARD_LEFT, BLOCK_SIZE_PIXELS);
			
		// display window contents
		window.display();
	}
}

int main()
{

	Game game;
	game.playGame();

	
	return 0;
}
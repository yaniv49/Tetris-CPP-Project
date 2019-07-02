#ifndef _TETRIS_GAME_H_
#define _TETRIS_GAME_H_

#include <iostream>
#include "Menu.h"
#include "point.h"
#include "Shape.h"
#include "Square.h"
#include "Line.h"
#include "Gamma.h"
#include "Pyramid.h"
#include "Skew.h"
#include "Joker.h"
#include "Bomb.h"
#include "time.h"
#include "Constants.h"
#include <conio.h>

using namespace std;

class TetrisGame {

	enum Shapes {SQUARE, LINE, GAMMA, PYRAMID, SKEW, JOKER, BOMB};

	Menu menu;
	char board[rows][cols];
	int piecesCounter;
	int scoreCounter;
	int linesCounter;
	double level;
	double timeEffect;
	bool gameOver;
	bool exit;
	char keyPressed;

	Point pieces;
	Point score;
	Point info;

	//Show the game's graphic design 
	void drawGame() const;

	//Initialing the game's variables
	void initGame();

	//Reset necessary variables when a new game is starting
	void resetGame();

	//Reset board values
	void resetBoard();

	//Update pieces counter and show the result on screen
	void updatePieces();

	//Update the score and show the result on screen
	void updateScore(int add);

	//Setting a shape on it's initial coordinates
	Shape* setShape(int randomShape);

	//Checking if user got a full line
	bool fullLine(int line) const;

	//Check the whole board in order to find full lines
	//This fuction cosidered if joker was used for score calculation
	void checkLines(bool joker);
	
	//Remove full line from board
	void removeLine(int line);

	//fix board after removing a full line
	void fixBoard(int line);

	//Running the game 
	void playGame();

	//Hide the cursor
	void hidecursor() const;

public:
	//Ctor
	TetrisGame();

	//The main function 
	void run();
};

#endif
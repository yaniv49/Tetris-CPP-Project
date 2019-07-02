#ifndef _JOKER_H_
#define _JOKER_H_

#include "Shape.h"
#include "Point.h"
#include "Keys.h"
#include "time.h"
#include "Menu.h"
#include "Colors.h"
#include "Constants.h"
#include <conio.h>

using namespace std;

class Joker : public Shape {

	Point body[specialShapeSize];
	bool stay;

	//Moving shape according to user's hit
	void move(char board[rows][cols], char keyPressed = 0);

	//Set shape on board
	void setOnBoard(char board[rows][cols]) const;

	//Ceck if erase shape is needed
	//If location is on another shape, erase isn't necessary
	bool erase(char board[rows][cols]) const;

	bool canMoveLeft(char board[rows][cols]) const;
	bool canMoveRight(char board[rows][cols]) const;
	bool canMoveDown(char board[rows][cols]) const;

public:
	//Ctor
	Joker();

	//Start playing with shape
	void play(char board[rows][cols], double& level, double& timeEffect, Menu& menu, bool& gameOver, bool& exit, char& keyPressed);
};

#endif
#ifndef _BOMB_H_
#define _BOMB_H_

#include "Shape.h"
#include "Point.h"
#include "Menu.h"
#include "time.h"
#include "Colors.h"
#include "Constants.h"
#include <conio.h>

using namespace std;

class Bomb : public Shape {
	Point body[specialShapeSize];
	bool bomb;

	//Draw the shape on screen
	void draw(char c = '*') const;

	//Remove pieces after bomb effect
	void remove(char board[rows][cols], int line, int from, int to) const;

	//fix board after bomb effect
	void fix(char board[rows][cols], int line, int from, int to) const;

	bool canMoveLeft(char board[rows][cols]) const;
	bool canMoveRight(char board[rows][cols]) const;
	bool canMoveDown(char board[rows][cols]) const;

public:
	//Ctor
	Bomb();

	//Start playing with shape
	void play(char board[rows][cols], double& level, double& timeEffect, Menu& menu, bool& gameOver, bool& exit, char& keyPressed);

	//Calculate the number of parts that were bombed
	//Finally in use to decrease score
	int getNumOfParts(char board[rows][cols], double timeEffect) const;

	//Making the bomb effect
	void boom(char board[rows][cols]) const;
};

#endif
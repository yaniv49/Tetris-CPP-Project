#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Point.h"
#include "Keys.h"
#include "time.h"
#include "Menu.h"
#include "Constants.h"
#include <conio.h>

using namespace std;

class Shape {
protected:
	int size;
	char color;
	Point* Body;
	bool shouldRotate;

	//Draw the shape on screen
	virtual void draw(char c = '*') const;

	//Moving shape according to user's hit
	virtual void move(char board[rows][cols], char keyPressed = 0);

	//Set shape on board
	virtual void setOnBoard(char board[rows][cols]) const;

	//Rotate shape according to user's hit
	virtual void rotate(char board[rows][cols]);

	virtual bool canMoveLeft(char board[rows][cols]) const;
	virtual bool canMoveRight(char board[rows][cols]) const;
	virtual bool canMoveDown(char board[rows][cols]) const;

	void moveLeft();
	void moveRight();
	void moveDown();


public:
	//Ctor
	Shape(int bodySize, char shapeColor, Point* body, bool rotate);
	
	//virtual ~Shape();

	//Start playing with shape
	virtual void play(char board[rows][cols], double& level, double& timeEffect, Menu& menu, bool& gameOver, bool& exit, char& keyPressed);
};

#endif
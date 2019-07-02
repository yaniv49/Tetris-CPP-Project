#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "Gotoxy.h"
#include "time.h"
#include "Constants.h"

using namespace std;

class Point {
	int x, y;
	
public:
	//Ctor
	Point(int _x = 0, int _y = 0);

	//Draw a chracter on point's coordinates
	void draw(char c = '*', char color = 7) const;

	//Print an integer on point's coordinates
	void print(int num, char color = 7) const;

	//Print a string on point's coordinates
	void show(string info, char color = 7) const;

	//Clear screen on point's coordinates
	void clear(int length) const;

	//Moving point up
	void up();

	//Moving point down
	void down();

	//Moving point right
	void right();

	//Moving point left
	void left();
	
	//Ceck if the point is on the board's range
	bool inBoard() const;

	//Making a flash effect on point's coordinates
	void flash(double time, char color) const;

	//Setting coordinates
	void setXY(int _x, int _y);

	int getX() const;
	int getY() const;
};

#endif
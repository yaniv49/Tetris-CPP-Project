#ifndef _PYRAMID_H_
#define _PYRAMID_H_

#include "Shape.h"
#include "Point.h"
#include "Colors.h"
#include "Constants.h"

using namespace std;

class Pyramid : public Shape {
	Point body[regularShapeSize];
	int state;

	//Rotate shape according to user's hit
	void rotate(char board[rows][cols]);

public:
	//Ctor
	Pyramid();
};

#endif
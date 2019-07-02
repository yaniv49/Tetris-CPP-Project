#ifndef _GAMMA_H_
#define _GAMMA_H_

#include "Shape.h"
#include "Point.h"
#include "Colors.h"
#include "Constants.h"

using namespace std;

class Gamma : public Shape {
	Point body[regularShapeSize];
	int state;

	//Rotate shape according to user's hit
	void rotate(char board[rows][cols]);

public:
	//Ctor
	Gamma();
};

#endif
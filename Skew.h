#ifndef _SKEW_H_
#define _SKEW_H_

#include "Shape.h"
#include "Point.h"
#include "Colors.h"
#include "Constants.h"

using namespace std;

class Skew : public Shape {
	Point body[4];
	int state;

	//Rotate shape according to user's hit
	void rotate(char board[rows][cols]);

public:
	//Ctor
	Skew();
};

#endif

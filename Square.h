#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "Shape.h"
#include "Point.h"
#include "Colors.h"
#include "Constants.h"

using namespace std;

class Square : public Shape {
	Point body[regularShapeSize];

public:
	//Ctor
	Square();
};

#endif
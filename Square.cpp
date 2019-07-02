#include "Square.h"

Square::Square() : Shape(regularShapeSize, Colors::Yellow, body, false) {
	body[0].setXY(0, 4);
	body[1].setXY(0, 5);
	body[2].setXY(1, 4);
	body[3].setXY(1, 5);
	
	draw();
}
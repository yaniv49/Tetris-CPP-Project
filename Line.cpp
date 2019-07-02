#include "Line.h"

Line::Line() : Shape(regularShapeSize, Colors::LightBlue, body, true) {
	body[0].setXY(0, 3);
	body[1].setXY(0, 4);
	body[2].setXY(0, 5);
	body[3].setXY(0, 6);

	state = state0;
	draw();
}

void Line::rotate(char board[rows][cols]) {

	int x0 = body[0].getX(), y0 = body[0].getY();
	int x1 = body[1].getX(), y1 = body[1].getY();
	int x2 = body[2].getX(), y2 = body[2].getY();
	int x3 = body[3].getX(), y3 = body[3].getY();

	int newState = (state + 1) % states;

	if (state == state0 && x2 > minXcoord && x2 < maxXcoord - 1 && !board[x2 - 1][y2] && !board[x2 + 1][y2] && !board[x2 + 2][y2]) {
		body[0].setXY(x2 - 1, y2);
		body[1].setXY(x2, y2);
		body[2].setXY(x2 + 1, y2);
		body[3].setXY(x2 + 2, y2);
		state = newState;
	}
	else if (state == state1 && y2 < maxYcoord && y2 > minYcoord + 1 && !board[x2][y2 + 1] && !board[x2][y2 - 1] && !board[x2][y2 - 2]) {
		body[0].setXY(x2, y2 + 1);
		body[1].setXY(x2, y2);
		body[2].setXY(x2 , y2 - 1);
		body[3].setXY(x2 , y2 - 2);
		state = newState;
	}
	else if (state == state2 && x2 < maxXcoord && x2 > minXcoord + 1 && !board[x2 + 1][y2] && !board[x2 - 1][y2] && !board[x2 - 2][y2]) {
		body[0].setXY(x2 + 1, y2);
		body[1].setXY(x2, y2);
		body[2].setXY(x2 - 1, y2);
		body[3].setXY(x2 - 2, y2);
		state = newState;
	}
	else if (state == state3 && y2 > minYcoord && y2 < maxYcoord - 1 && !board[x2][y2 - 1] && !board[x2][y2 + 1] && !board[x2][y2 + 2]) {
		body[0].setXY(x2, y2 - 1);
		body[1].setXY(x2, y2);
		body[2].setXY(x2, y2 + 1);
		body[3].setXY(x2, y2 + 2);
		state = newState;
	}

	draw();
}
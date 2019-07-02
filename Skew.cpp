#include "Skew.h"

Skew::Skew() : Shape(regularShapeSize, Colors::Green, body, true) {
	body[0].setXY(0, 3);
	body[1].setXY(0, 4);
	body[2].setXY(1, 4);
	body[3].setXY(1, 5);

	state = state0;
	draw();
}

void Skew::rotate(char board[rows][cols]) {

	int x0 = body[0].getX(), y0 = body[0].getY();
	int x1 = body[1].getX(), y1 = body[1].getY();
	int x2 = body[2].getX(), y2 = body[2].getY();
	int x3 = body[3].getX(), y3 = body[3].getY();

	int newState = (state + 1) % states;

	if (state == state0 && x2 < maxXcoord && !board[x1][y1 + 1] && !board[x2 + 1][y2]) {
		body[0].setXY(x1, y1 + 1);
		body[1].setXY(x3, y3);
		body[3].setXY(x2 + 1, y2);
		state = newState;
	}
	else if (state == state1 && y2 > minYcoord && !board[x2][y2 - 1] && !board[x1 + 1][y1]) {
		body[0].setXY(x1 + 1, y1);
		body[1].setXY(x3, y3);
		body[3].setXY(x2, y2 - 1);
		state = newState;
	}
	else if (state == state2 && x2 > minXcoord && !board[x2 - 1][y2] && !board[x1][y1 - 1]) {
		body[0].setXY(x1, y1 - 1);
		body[1].setXY(x3, y3);
		body[3].setXY(x2 - 1, y2);
		state = newState;
	}
	else if (state == state3 && y2 < maxYcoord && !board[x2][y2 + 1] && !board[x1 - 1][y1]) {
		body[0].setXY(x1 - 1, y1);
		body[1].setXY(x3, y3);
		body[3].setXY(x2, y2 + 1);
		state = newState;
	}

	draw();
}
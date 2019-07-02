#include "Shape.h"

Shape::Shape(int bodySize, char shapeColor, Point* body, bool rotate) :
	size(bodySize), color(shapeColor), Body(body), shouldRotate(rotate) {
}

//Shape::~Shape() {}

bool Shape::canMoveLeft(char board[rows][cols]) const {
	for (int i = 0; i < size; i++) {
		int x = Body[i].getX(), y = Body[i].getY();
		if (board[x][y - 1] || !Point(x, y - 1).inBoard()) {
			return false;
		}
	}
	return true;
}

bool Shape::canMoveRight(char board[rows][cols]) const {
	for (int i = 0; i < size; i++) {
		int x = Body[i].getX(), y = Body[i].getY();
		if (board[x][y + 1] || !Point(x, y + 1).inBoard()) {
			return false;
		}
	}
	return true;
}

bool Shape::canMoveDown(char board[rows][cols]) const {
	for (int i = 0; i < size; i++) {
		int x = Body[i].getX(), y = Body[i].getY();
		if (board[x + 1][y] || !Point(x + 1, y).inBoard()) {
			return false;
		}
	}
	return true;
}

void Shape::play(char board[rows][cols], double& level, double& timeEffect, Menu& menu, bool& gameOver, bool& exit, char& keyPressed) {
	size_t start = clock(), now;
	while (true) {
		if (canMoveDown(board)) {
			if (_kbhit()) {
				keyPressed = _getch();
				_flushall();
				//Checkin user's hit
				menu.checkKey(keyPressed, level, timeEffect, gameOver, exit);
				if (gameOver || exit) break;
				move(board, keyPressed);
			}
			now = clock();
			//Checking time according to game's level
			//Shape is moving down automatically 
			if (now - start >= level) {
				move(0);
				start = now;
			}
		}

		//Else if shape need to stop, user can change it's position last time 
		else {
			now = clock();
			if (_kbhit()) {
				keyPressed = _getch();
				_flushall();
				menu.checkKey(keyPressed, level, timeEffect, gameOver, exit);
				if (gameOver || exit) break;
				move(board, keyPressed);
			}
			if (now - start >= level) {
				break;
			}
		}

	}
	//Settint shape on board at last
	setOnBoard(board);
}

void Shape::setOnBoard(char board[rows][cols]) const {
	for (int i = 0; i < size; i++) {
		board[Body[i].getX()][Body[i].getY()] = color;
	}
}

void Shape::draw(char c) const {
	for (int i = 0; i < size; i++) {
		Body[i].draw(c, color);
		//cout << "in Shape draw";
	}
}

void Shape::move(char board[rows][cols], char keyPressed) {
	int x0 = Body[0].getX(), y0 = Body[0].getY();
	int x1 = Body[1].getX(), y1 = Body[1].getY();
	int x2 = Body[2].getX(), y2 = Body[2].getY();
	int x3 = Body[3].getX(), y3 = Body[3].getY();

	draw(' ');

	if (keyPressed == Keys::LEFT && canMoveLeft(board)) {
		moveLeft();
	}

	else if (keyPressed == Keys::RIGHT && canMoveRight(board)) {
		moveRight();
	}

	else if (keyPressed == Keys::DOWN && canMoveDown(board)) {
		moveDown();
	}

	else if (keyPressed == Keys::ROTATE && shouldRotate) {
		rotate(board);
	}

	else if (keyPressed == 0) {
		moveDown();
	}

	draw();
}

void Shape::moveLeft() {
	for (int i = 0; i < size; i++) {
		Body[i].left();
	}
}

void Shape::moveRight() {
	for (int i = 0; i < size; i++) {
		Body[i].right();
	}
}

void Shape::moveDown() {
	for (int i = 0; i < size; i++) {
		Body[i].down();
	}
}

void Shape::rotate(char board[rows][cols]) {}
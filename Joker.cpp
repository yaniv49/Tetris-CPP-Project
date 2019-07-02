#include "Joker.h"

Joker::Joker() : Shape(specialShapeSize, Colors::White, body, false) {
	body[0].setXY(0, 4);
	stay = false;
	draw();
}

void Joker::play(char board[rows][cols], double& level, double& timeEffect, Menu& menu, bool& gameOver, bool& exit, char& keyPressed) {
	size_t start = clock(), now;
	while (true) {
		if (!stay && canMoveDown(board)) {
			if (_kbhit()) {
				keyPressed = _getch();
				_flushall();
				//Checkin user's hit
				menu.checkKey(keyPressed, level, timeEffect, gameOver, exit);
				if (gameOver || exit) break;
				//Checking if joker is on another shape. true meaning not to erase it's location
				if (erase(board)) {
					draw(' ');
				}
				//Taking previous coordinate's in order to return previous phase after joker passed
				Point prev(body[0].getX(), body[0].getY());
				move(board, keyPressed);
				// Returns previous phase after joker passed, if necessary
				if (board[prev.getX()][prev.getY()]) {
					prev.draw('*', board[prev.getX()][prev.getY()]);
				}
			}
			now = clock();
			//Checking time according to game's level
			//Shape is moving down automatically 
			if (now - start >= level) {
				if (erase(board)) {
					draw(' ');
				}
				Point prev(body[0].getX(), body[0].getY());
				move(0);
				if (board[prev.getX()][prev.getY()]) {
					prev.draw('*', board[prev.getX()][prev.getY()]);
				}
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
				if (erase(board)) {
					draw(' ');
				}
				Point prev(body[0].getX(), body[0].getY());
				move(board, keyPressed);
				if (board[prev.getX()][prev.getY()]) {
					prev.draw('*', board[prev.getX()][prev.getY()]);
				}
			}
			if (now - start >= level || stay) {
				break;
			}
		}
	}
	//Settint shape on board at last
	setOnBoard(board);
}

bool Joker::erase(char board[rows][cols]) const{
	return !board[body[0].getX()][body[0].getY()];
}

void Joker::setOnBoard(char board[rows][cols]) const {
	int x0 = body[0].getX(), y0 = body[0].getY();
	board[x0][y0] = color;
	Point(x0, y0).draw('*', color);
}

void Joker::move(char board[rows][cols], char keyPressed) {

	int x0 = body[0].getX(), y0 = body[0].getY();
			
	if (keyPressed == Keys::LEFT && canMoveLeft(board)) {
		moveLeft();
	}

	else if (keyPressed == Keys::RIGHT && canMoveRight(board)) {
		moveRight();
	}

	else if (keyPressed == Keys::DOWN && canMoveDown(board)) {
		moveDown();
	}

	else if (keyPressed == Keys::STAY) {
		stay = true;
	}

	else if (keyPressed == 0) {
		moveDown();
	}

	draw();
}

bool Joker::canMoveLeft(char board[rows][cols]) const {
	int x = body[0].getX(), y = body[0].getY();
	return Point(x, y - 1).inBoard();
}

bool Joker::canMoveRight(char board[rows][cols]) const {
	int x = body[0].getX(), y = body[0].getY();
	return Point(x, y + 1).inBoard();
}

bool Joker::canMoveDown(char board[rows][cols]) const {
	int x = body[0].getX(), y = body[0].getY();
	return Point(x + 1, y).inBoard();
}
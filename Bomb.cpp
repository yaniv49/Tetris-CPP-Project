#include "Bomb.h"

Bomb::Bomb() : Shape(specialShapeSize, Colors::Red, body, false) {
	body[0].setXY(0, 4);
	bomb = false;
	draw();
}

void Bomb::play(char board[rows][cols], double& level, double& timeEffect, Menu& menu, bool& gameOver, bool& exit, char& keyPressed) {
	size_t start = clock(), now;
	while (true) {
		if (!bomb && canMoveDown(board)) {
			if (_kbhit()) {
				keyPressed = _getch();
				_flushall();
				//Checkin user's hit
				menu.checkKey(keyPressed, level, timeEffect, gameOver, exit);
				if (gameOver || exit) break;
				move(board, keyPressed);
				//Checking if bomb need to take action
				if (board[body[0].getX()][body[0].getY()] || !canMoveDown(board)) {
					bomb = true;
				}
			}
			now = clock();
			//Checking time according to game's level
			//Shape is moving down automatically 
			if (now - start >= level) {
				move(0);
				if (board[body[0].getX()][body[0].getY()] || !canMoveDown(board)) {
					bomb = true;
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
				move(board, keyPressed);
				if (board[body[0].getX()][body[0].getY()]) {
					bomb = true;
				}
			}
			if (now - start >= level || bomb) {
				break;
			}
		}
	}
}

bool Bomb::canMoveLeft(char board[rows][cols]) const {
	int x = body[0].getX(), y = body[0].getY();
	return Point(x, y - 1).inBoard();
}

bool Bomb::canMoveRight(char board[rows][cols]) const {
	int x = body[0].getX(), y = body[0].getY();
	return Point(x, y + 1).inBoard();
}

bool Bomb::canMoveDown(char board[rows][cols]) const {
	int x = body[0].getX(), y = body[0].getY();
	return Point(x + 1, y).inBoard();
}

void Bomb::draw(char c) const {
	if (c == '*') { c = '@'; }
	body[0].draw(c, color);
}

int Bomb::getNumOfParts(char board[rows][cols], double timeEffect) const {
	int x = body[0].getX(), y = body[0].getY();
	int parts = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			Point p(i, j);
			if (p.inBoard() && board[i][j]) {
				parts++;
			}
			if (p.inBoard()) {
				board[i][j] = 0;
				p.flash(timeEffect, Colors::Red);
				p.draw(' ');
			}

		}
	}
	return parts;
}

void Bomb::remove(char board[rows][cols], int line, int from, int to) const {
	for (int j = from; j <= to; j++) {
		char color = board[line][j];
		board[line][j] = 0;
		Point p(line, j);
		p.draw(' ');
	}
}

void Bomb::fix(char board[rows][cols], int line, int from, int to) const {
	if (line == 0) return;
	for (int j = from; j <= to; j++) {
		board[line][j] = board[line - 1][j];
		Point(line, j).draw('*', board[line - 1][j]);
	}
	fix(board, line - 1, from, to);
}

void Bomb::boom(char board[rows][cols]) const {
	int x = body[0].getX(), y = body[0].getY();
	int underLine = x, topLine = x, from = y, to = y;

	if (Point(x + 1, y).inBoard()) {
		underLine = x + 1;
	}

	if (Point(x - 1, y).inBoard()) {
		topLine = x - 1;
	}

	if (Point(x, y - 1).inBoard()) {
		from = y - 1;
	}

	if (Point(x, y + 1).inBoard()) {
		to = y + 1;
	}

	for (int i = underLine; i >= topLine; i--) {
		remove(board, underLine, from, to);
		fix(board, underLine, from, to);
	}
}
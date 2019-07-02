#include "Point.h"

Point::Point(int _x, int _y): x(_x), y(_y) {}

void Point::draw(char c, char color) const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	int x_coord = y + 67;
	int y_coord = x + 4;
	gotoxy(x_coord, y_coord);
	cout << c;
	cout.flush();
}

void Point::print(int num, char color) const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	gotoxy(x, y);
	cout << num;
	cout.flush();
}

void Point::show(string info, char color) const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	for (unsigned int i = 0; i < info.length(); i++) {
		gotoxy(x + i, y);
		cout << info[i];
		cout.flush();
	}
}

void Point::clear(int length) const {
	for (int i = 0; i < length ; i++) {
		gotoxy(x + i, y);
		cout << ' ';
		cout.flush();
	}
}

void Point::up() { x = x - 1; }
void Point::down() { x = x + 1; }
void Point::right() { y = y + 1; }
void Point::left() { y = y - 1; }

bool Point::inBoard() const { 
	return x >= minXcoord && x <= maxXcoord && y >= minYcoord && y <= maxYcoord; 
}

void Point::flash(double time, char color) const {
	size_t start = clock(), now = clock();
	while (now - start < time) {
		draw('*', color);
		draw(' ');
		now = clock();
	}
}

void Point::setXY(int _x, int _y) { x = _x; y = _y; }

int Point::getX() const { return x; }
int Point::getY() const { return y; }
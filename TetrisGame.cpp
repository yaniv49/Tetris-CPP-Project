#include "TetrisGame.h"

TetrisGame::TetrisGame() {
	hidecursor();
	drawGame();
	initGame();
	resetGame();
}

void TetrisGame::run() {
	keyPressed = 0;
	while (!exit) {
		if (_kbhit()) {
			keyPressed = _getch();
		}
		
		//If a new game was required
		if (menu.checkKey(keyPressed, level, timeEffect, gameOver, exit)) {
			keyPressed = 0;
			resetGame();
			playGame();
		}
	}
	info.clear(infoLength);
	info.show("             Good Bye!                ");
	cout << endl;
}

void TetrisGame::playGame() {
	Shape* shape;
	gameOver = false;
	
	while (!exit) {
		int randomShape = rand() % numOfShapes;
		shape = setShape(randomShape);

		if (gameOver) {
			break;
		}

		updatePieces();
		shape->play(board, level, timeEffect, menu, gameOver, exit, keyPressed);

		if (exit || gameOver) break;
		
		if (randomShape == BOMB) {
			int parts = ((Bomb*)shape)->getNumOfParts(board, timeEffect);
			((Bomb*)shape)->boom(board);
			int decrease = ((decScoreForPiece) * parts);
			updateScore(decrease);
		}

		if (randomShape == JOKER) {
			//Checink lines, joker used
			checkLines(true);
		}

		else {
			//Checink lines but no joker used
			checkLines(false);
		}

		delete shape;

	}

	info.clear(infoLength);
	info.show("             Game over!               ");
}

Shape* TetrisGame::setShape(int randomShape) {
	Shape* shape = nullptr;
	switch (randomShape) {
	case SQUARE:
		shape = new Square();
		if (board[0][4] || board[0][5] || board[1][4] || board[1][5]) {
			gameOver = true;
		}
		break;
	case LINE:
		shape = new Line();
		if (board[0][3] || board[0][4] || board[0][5] || board[0][6]) {
			gameOver = true;
		}
		break;
	case GAMMA:
		shape = new Gamma();
		if (board[0][3] || board[1][3] || board[1][4] || board[1][5]) {
			gameOver = true;
		}
		break;
	case SKEW:
		shape = new Skew();
		if (board[0][3] || board[0][4] || board[1][4] || board[1][5]) {
			gameOver = true;
		}
		break;
	case PYRAMID:
		shape = new Pyramid();
		if (board[0][4] || board[1][3] || board[1][4] || board[1][5]) {
			gameOver = true;
		}
		break;
	case JOKER:
		shape = new Joker();
		break;
	case BOMB:
		shape = new Bomb();
		break;
	}

	return shape;
}

void TetrisGame::checkLines(bool joker) {
	bool jokerUsed = joker;
	for (int line = maxXcoord; line >= minXcoord; line--) {
		if (fullLine(line)) {
			linesCounter++;
			removeLine(line);

			//If user made 20 lines, level up automatically
			if (linesCounter % linesToLevelUp == 0 && level != maxLevel) {
				level -= levelChange;
				timeEffect -= timeEffectChange;
			}

			if (jokerUsed) {
				updateScore(scoreForJokerUsed);
				jokerUsed = false;
			}

			else {
				updateScore(scoreForFullLine);
			}

			//Fix the board after line was removed
			fixBoard(line);
			line++;
		}
	}
}

bool TetrisGame::fullLine(int line) const {
	for (char val : board[line]) {
		if (!val) return false;
	}
	return true;
}

void TetrisGame::removeLine(int line) {
	for (int j = minYcoord; j <= maxYcoord; j++) {
		char color = board[line][j];
		board[line][j] = 0;
		Point p(line, j);
		p.flash(timeEffect, color);
		p.draw(' ');
	}
}

void TetrisGame::fixBoard(int line) {
	if (line == minXcoord) return;
	for (int j = minYcoord; j <= maxYcoord; j++) {
		board[line][j] = board[line - 1][j];
		Point(line, j).draw('*', board[line - 1][j]);
	}
	fixBoard(line - 1);
}

void TetrisGame::updatePieces() {
	piecesCounter++;
	pieces.print(piecesCounter);
}

void TetrisGame::updateScore(int add) {
	scoreCounter += add;

	score.clear(scoreLength);

	if (scoreCounter < 0) {
		scoreCounter = 0;
	}
	
	score.print(scoreCounter);
}

void TetrisGame::resetGame() {
	exit = false;
	gameOver = true;
	level = minLevel;
	piecesCounter = 0;
	scoreCounter = 0;
	linesCounter = 0;
	resetBoard();
	info.clear(infoLength);
	score.clear(scoreLength);
	pieces.clear(piecesLength);
	score.print(0);
	pieces.print(0);
}

void TetrisGame::initGame() {
	level = minLevel; //miliseconds
	timeEffect = effectTime; //miliseconds

	//Setting coordinates for relevant information on screen
	score.setXY(scoreXcoord, scoreYcoord);
	pieces.setXY(piecesXcoord, piecesYcoord);
	info.setXY(infoXcoord, infoYcoord);
}

void TetrisGame::resetBoard() {
	for (int i = minXcoord; i <= maxXcoord; i++) {
		for (int j = minYcoord; j <= maxYcoord; j++) {
			board[i][j] = 0;
			Point(i, j).draw(' ');
		}
	}
}

void TetrisGame::drawGame() const {
	cout << "                                   _________________________________________________ \n";
	cout << "                                  |         __             |    Score:              |\n";
	cout << "                                  |   |\\/| |__ |\\ | |  |   |    Pieces:             |\n";
	cout << "                                  |   |  | |__ | \\| |__|   |       ----------       |\n";
	cout << "                                  |                        |      |          |      |\n";
	cout << "                                  |                        |      |          |      |\n";
	cout << "                                  |  Start Game    (Enter) |      |          |      |\n";
	cout << "                                  |                        |      |          |      |\n";
	cout << "                                  |                        |      |          |      |\n";
	cout << "                                  |  Pause / Play  (Space) |      |          |      |\n";
	cout << "                                  |                        |      |          |      |\n";
	cout << "                                  |                        |      |          |      |\n";
	cout << "                                  |  Level Up      (u)     |      |          |      |\n";
	cout << "                                  |                        |      |          |      |\n";
	cout << "                                  |                        |      |          |      |\n";
	cout << "                                  |  Level Down    (d)     |      |          |      |\n";
	cout << "                                  |                        |      |          |      |\n";
	cout << "                                  |                        |      |          |      |\n";
	cout << "                                  |  Quit          (ESC)   |      |          |      |\n";
	cout << "                                  |                        |       ----------       |\n";
	cout << "                                  |________________________|________________________|\n";
	cout << endl;
}

void TetrisGame::hidecursor() const {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = infoDWsize;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
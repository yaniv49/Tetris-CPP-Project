#include "Menu.h"

Menu::Menu() {
	info.setXY(infoXcoord, infoYcoord);
}

bool Menu::checkKey(char& keyPressed, double& level, double& timeEffect, bool& gameOver, bool& exit) const {

	if (keyPressed == START) {

		if (gameOver) {
			return true;
		}

		info.clear(infoLength);
		info.show("   (SPACE) Back  (START) New Game");

		while (!exit) {
			if (_kbhit()) {
				keyPressed = _getch();
				if (keyPressed == Keys::PAUSE) {
					info.clear(infoLength);
					break;
				}

				else if (keyPressed == START) {
					keyPressed = START;
					gameOver = true;
					break;
				}
				else if (keyPressed == ESC) {
					checkKey(keyPressed, level, timeEffect, gameOver, exit);
					if (keyPressed == Keys::PAUSE) { break; };
				}

				else {
					checkKey(keyPressed, level, timeEffect, gameOver, exit);
				}
			}

		}

	}

	else if (keyPressed == Keys::LEVEL_UP) {
		if (level != maxLevel) {
			level -= levelChange;
			timeEffect -= timeEffectChange;
		}
	}

	else if (keyPressed == Keys::LEVEL_DOWN) {
		if (level != minLevel) {
			level += levelChange;
			timeEffect += timeEffectChange;
		}
	}

	else if (keyPressed == Keys::PAUSE && !gameOver) {
		info.show("Paused  (SPACE) Back  (START) New Game");

		while (!exit) {
			if (_kbhit()) {
				keyPressed = _getch();
				if (keyPressed == Keys::PAUSE) {
					info.clear(infoLength);
					break;
				}

				else if (keyPressed == START) {
					keyPressed = START;
					gameOver = true;
					break;
				}
				else if (keyPressed == ESC) {
					checkKey(keyPressed, level, timeEffect, gameOver, exit);
					if (keyPressed == Keys::PAUSE) { break; };
				}

				else {
					checkKey(keyPressed, level, timeEffect, gameOver, exit);
				}
			}
		}
	}

	else if (keyPressed == ESC) {
		info.clear(infoLength);
		info.show("     (SPACE) Back  (ESC) Exit");

		while (!exit) {
			if (_kbhit()) {
				keyPressed = _getch();
				if (keyPressed == Keys::PAUSE) {
					info.clear(infoLength);
					break;
				}

				if (keyPressed == Keys::ESC) {
					gameOver = true;
					exit = true;
				}
			}
		}
	}
	return false;
}
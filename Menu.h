#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include "Point.h"
#include "Keys.h"
#include <conio.h>

using namespace std;

class Menu {
	//Point for relevant information on screen
	Point info;

public:
	//Ctor
	Menu();
	
	//Checking user's hit
	//This function controls game's flags for each action
	//Returns true if a new game was required
	bool checkKey(char& keyPressed, double& level, double& timeEffect, bool& gameOver, bool& exit) const;

};

#endif


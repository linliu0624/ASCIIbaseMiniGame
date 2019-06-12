#pragma once
#include<iostream>
#include "define.h"

struct bigmap {
	int type;
	int x;
	int y;
	bool playerPos;
};

struct roomObj {
	int type;
	int x;
	int y;
	bool playerPos = false;
	bool enemyPos = false;
	bool exitPos = false;
	bool mark = false;
};
extern bigmap dangeon[MAPRANGE][MAPRANGE];
extern roomObj room[ROOMRANGE][ROOMRANGE];
bool SearchRoom();
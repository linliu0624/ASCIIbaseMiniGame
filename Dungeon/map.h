#pragma once
#include<iostream>
#include "define.h"
struct bigmap {
	int type;
	int x;
	int y;
	bool playerPos;
}map[MAPRANGE][MAPRANGE];

struct roomObj {
	int type;
	int x;
	int y;
	bool playerPos = false;
	bool enemyPos = false;
}room[ROOMRANGE][ROOMRANGE];

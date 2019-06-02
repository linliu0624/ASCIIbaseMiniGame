#pragma once
#include "define.h"
#include "item.h"
struct unit {
	int type;
	int mapX;
	int mapY;
	int roomX;
	int firstRoomX;
	int roomY;
	int firstRoomY;
	int maxHp;
	int hp;
	material weapon;
	material armor;
	material inventory[64];
	bool alive;
	bool inventoryMode = false;
	bool samePosWithPlayer = false;
	char name[100];
};


#pragma once
#include "define.h"
#include "item.h"
struct unit {
	int type;
	int x;
	int y;
	int maxHp;
	int hp;
	material weapon;
	material armor;
	material inventory[64];
	bool alive;
	bool inventoryMode = false;
	char name[100];
};


#pragma once
#include "define.h"
#include "item.h"
struct unit {
	//�@�P
	int type;
	int mapX;
	int mapY;
	int roomX;
	int roomY;
	int maxHp;
	int hp;
	material weapon;
	material armor;
	material inventory[64];
	bool alive;
	
	
	//���a
	char name[100];
	bool inventoryMode = false;
	//�ĤH
	bool samePosWithPlayer = false;
	bool attackAble = false;
};

